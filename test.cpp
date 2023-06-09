

TEST(TestCaseName, test)
{

    {

        //modulo

        circular_queue<Node, 8> m_stack;


        EXPECT_EQ(m_stack.size(), 0);

        EXPECT_EQ(m_stack.empty(), true);
        EXPECT_EQ(m_stack.full(), false);

        m_stack.push({ 1,1 });

        EXPECT_EQ(m_stack.size(), 1);

        EXPECT_EQ(m_stack.empty(), false);

        EXPECT_EQ(m_stack.full(), false);
        m_stack.pop_front();

        EXPECT_EQ(m_stack.size(), 0);
        EXPECT_EQ(m_stack.empty(), true);
        EXPECT_EQ(m_stack.full(), false);

        m_stack.push({ 1,1 });
        m_stack.push({ 1,2 });
        m_stack.push({ 1,3 });
        m_stack.push({ 1,4 });
        m_stack.push({ 1,5 });
        m_stack.push({ 1,6 });
        m_stack.push({ 1,7 });

        EXPECT_EQ(m_stack.size(), 7);
        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), false);
        {
            const Node &n = m_stack.front();
            EXPECT_EQ(n.loaded, 1);
        }

        m_stack.pop_front();

        EXPECT_EQ(m_stack.size(), 6);

        m_stack.push({ 1,8 });

        EXPECT_EQ(m_stack.size(), 7);
        //tail back start
        m_stack.push({ 1,9 });

        EXPECT_EQ(m_stack.size(), 8);
        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), true);

        m_stack.push({ 1,10 });


        EXPECT_EQ(m_stack.size(), 8);
        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), true);

        //head moved
        {
            const Node &n = m_stack.front();
            EXPECT_EQ(n.loaded, 3);
        }

        m_stack.pop_front();
        EXPECT_EQ(m_stack.size(), 7);
        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), false);

        {
            const Node &n = m_stack.front();
            EXPECT_EQ(n.loaded, 4);
        }

        m_stack.clear();

        EXPECT_EQ(m_stack.size(), 0);
        EXPECT_EQ(m_stack.empty(), true);
        EXPECT_EQ(m_stack.full(), false);

        m_stack.push({ 1,1 });

        EXPECT_EQ(m_stack.size(), 1);

        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), false);


        {
            const Node &n = m_stack.front();
            EXPECT_EQ(n.loaded, 1);
        }

        m_stack.pop_front();

        EXPECT_EQ(m_stack.size(), 0);
        EXPECT_EQ(m_stack.empty(), true);
        EXPECT_EQ(m_stack.full(), false);
    }

    {

        // & operation

        circular_queue<Node, 8, false> m_stack;


        EXPECT_EQ(m_stack.size(), 0);

        EXPECT_EQ(m_stack.empty(), true);
        EXPECT_EQ(m_stack.full(), false);

        m_stack.push({ 1,1 });

        EXPECT_EQ(m_stack.size(), 1);

        EXPECT_EQ(m_stack.empty(), false);

        EXPECT_EQ(m_stack.full(), false);
        m_stack.pop_front();

        EXPECT_EQ(m_stack.size(), 0);
        EXPECT_EQ(m_stack.empty(), true);
        EXPECT_EQ(m_stack.full(), false);

        m_stack.push({ 1,1 });
        m_stack.push({ 1,2 });
        m_stack.push({ 1,3 });
        m_stack.push({ 1,4 });
        m_stack.push({ 1,5 });
        m_stack.push({ 1,6 });
        m_stack.push({ 1,7 });

        EXPECT_EQ(m_stack.size(), 7);
        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), true);

        {
            const Node &n = m_stack.front();
            EXPECT_EQ(n.loaded, 1);
        }

        m_stack.pop_front();

        EXPECT_EQ(m_stack.size(), 6);
        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), false);
        //tail back start
        m_stack.push({ 1,8 });

        EXPECT_EQ(m_stack.size(), 7);
        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), true);

        m_stack.push({ 1,9 });


        EXPECT_EQ(m_stack.size(), 7);
        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), true);

        //head moved
        {
            const Node &n = m_stack.front();
            EXPECT_EQ(n.loaded, 3);
        }

        m_stack.pop_front();
        EXPECT_EQ(m_stack.size(), 6);
        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), false);

        {
            const Node &n = m_stack.front();
            EXPECT_EQ(n.loaded, 4);
        }

        m_stack.clear();

        EXPECT_EQ(m_stack.size(), 0);
        EXPECT_EQ(m_stack.empty(), true);
        EXPECT_EQ(m_stack.full(), false);

        m_stack.push({ 1,1 });

        EXPECT_EQ(m_stack.size(), 1);

        EXPECT_EQ(m_stack.empty(), false);
        EXPECT_EQ(m_stack.full(), false);


        {
            const Node &n = m_stack.front();
            EXPECT_EQ(n.loaded, 1);
        }

        m_stack.pop_front();

        EXPECT_EQ(m_stack.size(), 0);
        EXPECT_EQ(m_stack.empty(), true);
        EXPECT_EQ(m_stack.full(), false);
    }

}