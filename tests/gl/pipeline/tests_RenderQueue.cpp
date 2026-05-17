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
        cmd.sortKey = PackedSortKey::zero();

        queue.submit(cmd);

        REQUIRE(queue.size() == 1);
        const RenderCommand& stored = queue.commands().front();
        CHECK(stored.instanceCount == 1);
        CHECK(stored.sortKey == SortKey::packOpaque(SortKey::OpaqueLayer, 0, 42u, 0));
    }

    TEST_CASE("submit preserves explicit sortKey")
    {
        RenderQueue queue;
        RenderCommand cmd;
        cmd.mesh = MeshHandle{ 1 };
        cmd.material = MaterialHandle{ 2 };
        cmd.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 999u, 0);

        queue.submit(cmd);

        REQUIRE(queue.size() == 1);
        CHECK(queue.commands().front().sortKey == SortKey::packOpaque(SortKey::OpaqueLayer, 0, 999u, 0));
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
        a.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 300u, 0);

        RenderCommand b;
        b.mesh = MeshHandle{ 2 };
        b.material = MaterialHandle{ 2 };
        b.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 100u, 0);

        RenderCommand c;
        c.mesh = MeshHandle{ 3 };
        c.material = MaterialHandle{ 3 };
        c.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 200u, 0);

        queue.submit(a);
        queue.submit(b);
        queue.submit(c);

        queue.sort(RenderQueue::Order::BySortKey);

        REQUIRE(queue.size() == 3);
        CHECK(queue.commands()[0].sortKey == SortKey::packOpaque(SortKey::OpaqueLayer, 0, 100u, 0));
        CHECK(queue.commands()[1].sortKey == SortKey::packOpaque(SortKey::OpaqueLayer, 0, 200u, 0));
        CHECK(queue.commands()[2].sortKey == SortKey::packOpaque(SortKey::OpaqueLayer, 0, 300u, 0));
    }

    TEST_CASE("sort BySubmission preserves submission order")
    {
        RenderQueue queue;

        RenderCommand a;
        a.mesh = MeshHandle{ 1 };
        a.material = MaterialHandle{ 1 };
        a.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 300u, 0);

        RenderCommand b;
        b.mesh = MeshHandle{ 2 };
        b.material = MaterialHandle{ 2 };
        b.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 100u, 0);

        queue.submit(a);
        queue.submit(b);

        queue.sort(RenderQueue::Order::BySubmission);

        REQUIRE(queue.size() == 2);
        CHECK(queue.commands()[0].sortKey == SortKey::packOpaque(SortKey::OpaqueLayer, 0, 300u, 0));
        CHECK(queue.commands()[1].sortKey == SortKey::packOpaque(SortKey::OpaqueLayer, 0, 100u, 0));
    }

    TEST_CASE("sort BySortKey is stable for equal sortKeys")
    {
        RenderQueue queue;

        RenderCommand a;
        a.mesh = MeshHandle{ 10 };
        a.material = MaterialHandle{ 1 };
        a.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 42u, 0);

        RenderCommand b;
        b.mesh = MeshHandle{ 20 };
        b.material = MaterialHandle{ 1 };
        b.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 42u, 0);

        queue.submit(a);
        queue.submit(b);

        queue.sort(RenderQueue::Order::BySortKey);

        REQUIRE(queue.size() == 2);
        CHECK(queue.commands()[0].mesh == MeshHandle{ 10 });
        CHECK(queue.commands()[1].mesh == MeshHandle{ 20 });
    }

    TEST_CASE("submit captures command by value")
    {
        RenderQueue queue;

        RenderCommand cmd;
        cmd.mesh = MeshHandle{ 11 };
        cmd.material = MaterialHandle{ 12 };
        cmd.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 1, 2, 3);

        queue.submit(cmd);

        cmd.mesh = MeshHandle{ 21 };
        cmd.material = MaterialHandle{ 22 };
        cmd.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 9, 9, 9);

        REQUIRE(queue.size() == 1);
        CHECK(queue.commands()[0].mesh == MeshHandle{ 11 });
        CHECK(queue.commands()[0].material == MaterialHandle{ 12 });
        CHECK(queue.commands()[0].sortKey == SortKey::packOpaque(SortKey::OpaqueLayer, 1, 2, 3));
    }

    TEST_CASE("sort BySortKey is idempotent")
    {
        RenderQueue queue;

        RenderCommand a;
        a.mesh = MeshHandle{ 1 };
        a.material = MaterialHandle{ 1 };
        a.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 300u, 0);

        RenderCommand b;
        b.mesh = MeshHandle{ 2 };
        b.material = MaterialHandle{ 2 };
        b.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 100u, 0);

        RenderCommand c;
        c.mesh = MeshHandle{ 3 };
        c.material = MaterialHandle{ 3 };
        c.sortKey = SortKey::packOpaque(SortKey::OpaqueLayer, 0, 200u, 0);

        queue.submit(a);
        queue.submit(b);
        queue.submit(c);

        queue.sort(RenderQueue::Order::BySortKey);
        const auto first = queue.commands();
        queue.sort(RenderQueue::Order::BySortKey);

        REQUIRE(queue.size() == first.size());
        CHECK(queue.commands()[0].mesh == first[0].mesh);
        CHECK(queue.commands()[1].mesh == first[1].mesh);
        CHECK(queue.commands()[2].mesh == first[2].mesh);
        CHECK(queue.commands()[0].sortKey == first[0].sortKey);
        CHECK(queue.commands()[1].sortKey == first[1].sortKey);
        CHECK(queue.commands()[2].sortKey == first[2].sortKey);
    }
}
