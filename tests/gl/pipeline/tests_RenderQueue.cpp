#include <doctest/doctest.h>

#include <nfx/Graphics.h>

using namespace nfx::graphics::gl;

TEST_SUITE("RenderQueue")
{
    TEST_CASE("submit accepts instanceCount == 1")
    {
        RenderQueue queue;
        RenderCommand cmd;
        cmd.mesh = MeshHandle{ 1 };
        cmd.material = MaterialHandle{ 2 };
        cmd.instanceCount = 1;

        queue.submit(cmd);

        REQUIRE(queue.size() == 1);
        CHECK(queue.commands().front().instanceCount == 1);
    }

    TEST_CASE("Default queue is empty")
    {
        RenderQueue queue;

        CHECK(queue.empty());
        CHECK(queue.size() == 0);
        CHECK(queue.commands().empty());
    }

    TEST_CASE("submit assigns default sortKey from material handle")
    {
        RenderQueue queue;
        RenderCommand cmd;
        cmd.mesh = MeshHandle{ 7 };
        cmd.material = MaterialHandle{ 42 };
        cmd.sortKey = 0;

        queue.submit(cmd);

        REQUIRE(queue.size() == 1);
        const RenderCommand& stored = queue.commands().front();
        CHECK(stored.instanceCount == 1);
        CHECK(stored.sortKey == 42);
    }

    TEST_CASE("submit preserves explicit sortKey")
    {
        RenderQueue queue;
        RenderCommand cmd;
        cmd.mesh = MeshHandle{ 1 };
        cmd.material = MaterialHandle{ 2 };
        cmd.sortKey = 999;

        queue.submit(cmd);

        REQUIRE(queue.size() == 1);
        CHECK(queue.commands().front().sortKey == 999);
    }

    TEST_CASE("commands preserve submission order")
    {
        RenderQueue queue;

        RenderCommand first;
        first.mesh = MeshHandle{ 10 };
        first.material = MaterialHandle{ 100 };

        RenderCommand second;
        second.mesh = MeshHandle{ 20 };
        second.material = MaterialHandle{ 200 };

        queue.submit(first);
        queue.submit(second);

        REQUIRE(queue.size() == 2);
        CHECK(queue.commands()[0].mesh == MeshHandle{ 10 });
        CHECK(queue.commands()[0].material == MaterialHandle{ 100 });
        CHECK(queue.commands()[1].mesh == MeshHandle{ 20 });
        CHECK(queue.commands()[1].material == MaterialHandle{ 200 });
    }

    TEST_CASE("clear removes all queued commands")
    {
        RenderQueue queue;

        RenderCommand cmd;
        cmd.mesh = MeshHandle{ 1 };
        cmd.material = MaterialHandle{ 2 };
        queue.submit(cmd);
        REQUIRE_FALSE(queue.empty());

        queue.clear();

        CHECK(queue.empty());
        CHECK(queue.size() == 0);
        CHECK(queue.commands().empty());
    }

    TEST_CASE("sort BySortKey reorders by ascending sortKey")
    {
        RenderQueue queue;

        RenderCommand a;
        a.mesh = MeshHandle{ 1 };
        a.material = MaterialHandle{ 1 };
        a.sortKey = 300;

        RenderCommand b;
        b.mesh = MeshHandle{ 2 };
        b.material = MaterialHandle{ 2 };
        b.sortKey = 100;

        RenderCommand c;
        c.mesh = MeshHandle{ 3 };
        c.material = MaterialHandle{ 3 };
        c.sortKey = 200;

        queue.submit(a);
        queue.submit(b);
        queue.submit(c);

        queue.sort(RenderQueue::Order::BySortKey);

        REQUIRE(queue.size() == 3);
        CHECK(queue.commands()[0].sortKey == 100);
        CHECK(queue.commands()[1].sortKey == 200);
        CHECK(queue.commands()[2].sortKey == 300);
    }

    TEST_CASE("sort BySubmission preserves submission order")
    {
        RenderQueue queue;

        RenderCommand a;
        a.mesh = MeshHandle{ 1 };
        a.material = MaterialHandle{ 1 };
        a.sortKey = 300;

        RenderCommand b;
        b.mesh = MeshHandle{ 2 };
        b.material = MaterialHandle{ 2 };
        b.sortKey = 100;

        queue.submit(a);
        queue.submit(b);

        queue.sort(RenderQueue::Order::BySubmission);

        REQUIRE(queue.size() == 2);
        CHECK(queue.commands()[0].sortKey == 300);
        CHECK(queue.commands()[1].sortKey == 100);
    }

    TEST_CASE("sort BySortKey is stable for equal sortKeys")
    {
        RenderQueue queue;

        RenderCommand a;
        a.mesh = MeshHandle{ 10 };
        a.material = MaterialHandle{ 1 };
        a.sortKey = 42;

        RenderCommand b;
        b.mesh = MeshHandle{ 20 };
        b.material = MaterialHandle{ 1 };
        b.sortKey = 42;

        queue.submit(a);
        queue.submit(b);

        queue.sort(RenderQueue::Order::BySortKey);

        REQUIRE(queue.size() == 2);
        CHECK(queue.commands()[0].mesh == MeshHandle{ 10 });
        CHECK(queue.commands()[1].mesh == MeshHandle{ 20 });
    }
}
