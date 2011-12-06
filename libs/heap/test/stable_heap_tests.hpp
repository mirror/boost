#include "common_heap_tests.hpp"

struct q_tester
{
    q_tester(int i = 0, int j = 0):
        value(i), id(j)
    {}

    bool operator< (q_tester const & rhs) const
    {
        return value < rhs.value;
    }

    bool operator>= (q_tester const & rhs) const
    {
        return value >= rhs.value;
    }

    bool operator== (q_tester const & rhs) const
    {
        return (value == rhs.value) && (id == rhs.id);
    }

    int value;
    int id;
};

std::ostream& operator<< (std::ostream& out, q_tester const & t)
{
    out << "[" << t.value << " " << t.id << "";
    return out;
}

typedef std::vector<q_tester> stable_test_data;

stable_test_data make_stable_test_data(int size, int same_count = 3,
                                       int offset = 0, int strive = 1)
{
    stable_test_data ret;

    for (int i = 0; i != size; ++i)
        for (int j = 0; j != same_count; ++j)
            ret.push_back(q_tester(i * strive + offset, j));
    return ret;
}

struct cmp1
{
    bool operator()(q_tester const & lhs, q_tester const & rhs)
    {
        return lhs.id > rhs.id;
    }
};

struct cmp2 {
    bool operator()(q_tester const & lhs, q_tester const & rhs)
    {
        return lhs.value < rhs.value;
    }
};

void fixup_test_data(stable_test_data & data)
{
    std::stable_sort(data.begin(), data.end(), cmp1());
    std::stable_sort(data.begin(), data.end(), cmp2());
}

template <typename pri_queue>
void pri_queue_stable_test_sequential_push(void)
{
    stable_test_data data = make_stable_test_data(test_size);

    pri_queue q;
    fill_q(q, data);
    fixup_test_data(data);
    check_q(q, data);
}

template <typename pri_queue>
void pri_queue_stable_test_sequential_reverse_push(void)
{
    stable_test_data data = make_stable_test_data(test_size);
    pri_queue q;
    stable_test_data push_data(data);
    std::stable_sort(push_data.begin(), push_data.end(), std::greater_equal<q_tester>());
    fill_q(q, push_data);
    check_q(q, data);
}


template <typename pri_queue>
void run_stable_heap_tests(void)
{
    pri_queue_stable_test_sequential_push<pri_queue>();
    pri_queue_stable_test_sequential_reverse_push<pri_queue>();
}
