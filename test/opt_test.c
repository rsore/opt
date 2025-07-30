#define OPT_AUTODEFINE_PRIMITIVES
#include "../opt.h"

#include "minitest.h"

typedef struct {
    int i;
    char c;
} Foo;
OPT_DEFINE(Foo);

MT_DEFINE_TEST(opt_init)
{
    {
        Opt(int) opt = OPT_INIT;
        MT_CHECK_THAT(!opt_has_value(&opt));
        MT_CHECK_THAT(opt.value == 0);
    }
    {
        Opt(Foo) opt = OPT_INIT;
        MT_CHECK_THAT(!opt_has_value(&opt));
        MT_CHECK_THAT(opt.value.i == 0);
        MT_CHECK_THAT(opt.value.c == 0);
    }
}

MT_DEFINE_TEST(opt_make)
{
    {
        Opt(int) opt = OPT_MAKE(10);
        MT_CHECK_THAT(opt_has_value(&opt));
        MT_CHECK_THAT(opt.value == 10);
    }
    {
#ifndef __cplusplus
        Opt(Foo) opt = OPT_MAKE({.i = 1024, .c = 64});
#else
        Opt(Foo) opt = OPT_MAKE({1024, 64});
#endif
        MT_CHECK_THAT(opt_has_value(&opt));
        MT_CHECK_THAT(opt_get(&opt).i == 1024);
        MT_CHECK_THAT(opt_get(&opt).c == 64);
    }
}

MT_DEFINE_TEST(opt_set_value)
{
    Opt(int) opt = OPT_INIT;
    MT_ASSERT_THAT(!opt_has_value(&opt));

    opt_set(&opt, 42);
    MT_CHECK_THAT(opt_has_value(&opt));
    MT_CHECK_THAT(opt.value == 42);
}

MT_DEFINE_TEST(opt_get_value)
{
    Opt(int) opt = OPT_INIT;
    MT_ASSERT_THAT(!opt_has_value(&opt));

    opt_set(&opt, 69);
    MT_ASSERT_THAT(opt_has_value(&opt));
    MT_ASSERT_THAT(opt.value == 69);

    MT_CHECK_THAT(opt_get(&opt) == 69);
}

MT_DEFINE_TEST(opt_get_ptr)
{
    Opt(int) opt = OPT_INIT;
    MT_ASSERT_THAT(!opt_has_value(&opt));

    opt_set(&opt, 69);
    MT_ASSERT_THAT(opt_has_value(&opt));

    MT_CHECK_THAT(opt_get_ptr(&opt) == &opt.value);
}

MT_DEFINE_TEST(opt_get_or)
{
    {
        Opt(int) opt = OPT_INIT;
        MT_ASSERT_THAT(!opt_has_value(&opt));
        opt_set(&opt, 69);
        MT_CHECK_THAT(opt_get_or(&opt, 42) == 69);
    }
    {
        Opt(int) opt = OPT_INIT;
        MT_ASSERT_THAT(!opt_has_value(&opt));
        MT_CHECK_THAT(opt_get_or(&opt, 42) == 42);
    }
}

MT_DEFINE_TEST(opt_clear)
{
    Opt(int) opt = OPT_INIT;
    MT_ASSERT_THAT(!opt_has_value(&opt));

    opt_clear(&opt);
    MT_CHECK_THAT(!opt_has_value(&opt));

    opt_set(&opt, 69);
    MT_ASSERT_THAT(opt_has_value(&opt));

    opt_clear(&opt);
    MT_CHECK_THAT(!opt_has_value(&opt));
}


static void
run_all_tests(void)
{
    MT_RUN_TEST(opt_init);
    MT_RUN_TEST(opt_make);
    MT_RUN_TEST(opt_set_value);
    MT_RUN_TEST(opt_get_value);
    MT_RUN_TEST(opt_get_ptr);
    MT_RUN_TEST(opt_get_or);
    MT_RUN_TEST(opt_clear);
}

int
main(void)
{
    MT_INIT();

    run_all_tests();

    MT_PRINT_SUMMARY();
    return MT_EXIT_CODE;
}
