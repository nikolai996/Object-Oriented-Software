#define BOOST_TEST_MODULE MyTestModule

#include <boost/test/included/unit_test.hpp>
#include "Car.h"

struct CCarFixture
{
    CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CCarFixture)
    BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
    {
        BOOST_CHECK(!car.IsEngineOn());
    }

    BOOST_AUTO_TEST_CASE(cannot_select_gear_when_turned_off)
    {
        BOOST_CHECK(!car.SetGear(1));
        BOOST_CHECK_EQUAL(car.GetGear(), 0);
    }
    BOOST_AUTO_TEST_CASE(can_be_turned_on)
    {
        BOOST_CHECK(car.TurnOnEngine());
    }
    BOOST_AUTO_TEST_CASE(check_car_is_not_moving)
    {
        BOOST_CHECK_EQUAL(car.GetDirection(), 2);
    }

    BOOST_AUTO_TEST_CASE(cannot_set_speed_is_greater_than_0_for_neutral_gear)
    {
        BOOST_CHECK_EQUAL(car.GetGear(), 0);
        BOOST_CHECK(!car.SetSpeed(20));
        BOOST_CHECK_EQUAL(car.GetGear(), 0);
        BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
        BOOST_CHECK(car.SetSpeed(0));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
    }
    BOOST_AUTO_TEST_CASE(can_switching_to_neutral_when_transmission_is_neutral)
    {
        BOOST_CHECK(car.SetGear(0));
    }

    struct when_turned_on_ : CCarFixture
    {
        when_turned_on_()
        {
            car.TurnOnEngine();
        }
    };

    BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
        BOOST_AUTO_TEST_CASE(cannot_turned_on_if_already_turned_on)
        {
            BOOST_CHECK(!car.TurnOnEngine());
        }
        BOOST_AUTO_TEST_CASE(check_value_car_by_default)
        {
            BOOST_CHECK_EQUAL(car.GetGear(), 0);
            BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
        }
        BOOST_AUTO_TEST_CASE(can_switching_to_first_gear)
        {
            BOOST_CHECK(car.SetGear(1));
        }
        BOOST_AUTO_TEST_CASE(can_move_back_to_the_reverse_gear)
        {
            BOOST_CHECK(car.SetGear(-1));
            BOOST_CHECK(car.SetSpeed(-15));
            BOOST_CHECK_EQUAL(car.GetDirection(), 1);
        }
        BOOST_AUTO_TEST_CASE(can_turn_off_the_engine_in_neutral_gear)
        {
            BOOST_CHECK(car.SetGear(1));
            BOOST_CHECK(!car.TurnOffEngine());
            BOOST_CHECK(car.SetGear(-1));
            BOOST_CHECK(!car.TurnOffEngine());

            BOOST_CHECK(car.SetGear(0));
            BOOST_CHECK(car.TurnOffEngine());
        }

        struct when_first_gear_ : when_turned_on_
        {
            when_first_gear_()
            {
                car.SetGear(1);
            }
        };

        BOOST_FIXTURE_TEST_SUITE(when_first_gear, when_first_gear_)

            BOOST_AUTO_TEST_CASE(can_accelerates_from_0_to_30)
            {
                BOOST_CHECK(car.SetSpeed(0));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 0);

                BOOST_CHECK(car.SetSpeed(30));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 30);

                BOOST_CHECK(!car.SetSpeed(31));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
            }
            BOOST_AUTO_TEST_CASE(can_switching_to_neutral_gear)
            {
                BOOST_CHECK(car.SetGear(0));
            }
            BOOST_AUTO_TEST_CASE(can_switching_to_reverse_gear_when_velocity_is_0)
            {
                BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
                BOOST_CHECK(car.SetGear(-1));
            }
            BOOST_AUTO_TEST_CASE(can_switching_to_second_gear_when_velocity_is_20)
            {
                BOOST_CHECK(car.SetSpeed(20));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
                BOOST_CHECK(car.SetGear(2));
            }

        BOOST_AUTO_TEST_SUITE_END()

        struct in_neutral_gear_when_moving_ : when_first_gear_
        {
            in_neutral_gear_when_moving_()
            {
                car.SetSpeed(15);
                car.SetGear(0);
            }
        };
        BOOST_FIXTURE_TEST_SUITE(in_neutral_gear_when_moving, in_neutral_gear_when_moving_)
            BOOST_AUTO_TEST_CASE(cannot_increase_speed)
            {
                BOOST_CHECK(!car.SetSpeed(18));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 15);
            }
            BOOST_AUTO_TEST_CASE(can_enables_the_transmission_of_valid)
            {
                BOOST_CHECK(!car.SetGear(2));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 15);
                BOOST_CHECK(car.SetGear(1));
            }
            BOOST_AUTO_TEST_CASE(cannot_turn_off_engine)
            {
                BOOST_CHECK(!car.TurnOffEngine());
            }
            BOOST_AUTO_TEST_CASE(cannot_swithing_to_reverse_gear)
            {
                BOOST_CHECK(!car.SetGear(-1));
            }

        BOOST_AUTO_TEST_SUITE_END()

        struct when_second_gear_ : when_first_gear_
        {
            when_second_gear_()
            {
                car.SetSpeed(20);
                car.SetGear(2);
            }
        };

        BOOST_FIXTURE_TEST_SUITE(when_second_gear, when_second_gear_)
            BOOST_AUTO_TEST_CASE(can_accelerates_from_20_to_50)
            {
                BOOST_CHECK(!car.SetSpeed(19));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 20);

                BOOST_CHECK(car.SetSpeed(50));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 50);

                BOOST_CHECK(!car.SetSpeed(51));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
            }
            BOOST_AUTO_TEST_CASE(can_switching_to_first_gear_when_velocity_is_20)
            {
                BOOST_CHECK(car.SetSpeed(20));
                BOOST_CHECK(car.SetGear(1));
            }

            BOOST_AUTO_TEST_CASE(can_switching_to_third_gear_when_velocity_is_40)
            {
                BOOST_CHECK(car.SetSpeed(40));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 40);
                BOOST_CHECK(car.SetGear(3));
            }

            BOOST_AUTO_TEST_CASE(cannot_switching_to_reverse_gear_when_velocity_is_30)
            {
                BOOST_CHECK(car.SetSpeed(30));
                BOOST_CHECK(!car.SetGear(-1));
            }
            BOOST_AUTO_TEST_CASE(can_switching_to_neutral_gear)
            {
                BOOST_CHECK(car.SetGear(0));
            }
        BOOST_AUTO_TEST_SUITE_END()

        struct when_third_gear_ : when_second_gear_
        {
            when_third_gear_()
            {
                car.SetSpeed(30);
                car.SetGear(3);
            }
        };

        BOOST_FIXTURE_TEST_SUITE(when_third_gear, when_third_gear_)
            BOOST_AUTO_TEST_CASE(can_accelerates_from_30_to_60)
            {
                BOOST_CHECK(!car.SetSpeed(29));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 30);

                BOOST_CHECK(car.SetSpeed(60));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 60);

                BOOST_CHECK(!car.SetSpeed(61));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 60);
            }
        BOOST_AUTO_TEST_SUITE_END()

        struct when_fourth_gear_ : when_third_gear_
        {
            when_fourth_gear_()
            {
                car.SetSpeed(40);
                car.SetGear(4);
            }
        };

        BOOST_FIXTURE_TEST_SUITE(when_fourth_gear, when_fourth_gear_)
            BOOST_AUTO_TEST_CASE(can_accelerates_from_40_to_90)
            {
                BOOST_CHECK(!car.SetSpeed(39));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 40);

                BOOST_CHECK(car.SetSpeed(90));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 90);

                BOOST_CHECK(!car.SetSpeed(91));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 90);
            }
        BOOST_AUTO_TEST_SUITE_END()

        struct when_fifth_gear_ : when_fourth_gear_
        {
            when_fifth_gear_()
            {
                car.SetSpeed(50);
                car.SetGear(5);
            }
        };

        BOOST_FIXTURE_TEST_SUITE(when_fifth_gear, when_fifth_gear_)
            BOOST_AUTO_TEST_CASE(can_accelerates_from_50_to_150)
            {
                BOOST_CHECK(!car.SetSpeed(49));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 50);

                BOOST_CHECK(car.SetSpeed(150));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 150);

                BOOST_CHECK(!car.SetSpeed(151));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 150);
            }
        BOOST_AUTO_TEST_SUITE_END()

        struct when_reverse_gear_ : when_turned_on_
        {
            when_reverse_gear_()
            {
                car.SetGear(-1);
            }
        };

        BOOST_FIXTURE_TEST_SUITE(when_reverse_gear, when_reverse_gear_)

            BOOST_AUTO_TEST_CASE(can_accelerates_from_0_to_20)
            {
                BOOST_CHECK(car.SetSpeed(0));
                BOOST_CHECK_EQUAL(car.GetSpeed(), 0);


                BOOST_CHECK(!car.SetSpeed(21));
            }
            BOOST_AUTO_TEST_CASE(can_switching_to_first_gear_when_speed_is_0)
            {
                BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
                BOOST_CHECK(car.SetGear(1));
            }
            BOOST_AUTO_TEST_CASE(can_switching_to_neutral_gear_when_speed_is_greater_than_zero)
            {
                car.SetSpeed(10);
                BOOST_CHECK(car.SetGear(0));
            }
        BOOST_AUTO_TEST_SUITE_END()

    BOOST_AUTO_TEST_SUITE_END()

    struct when_turned_off_ : CCarFixture
    {
        when_turned_off_()
        {
            car.TurnOffEngine();
        }
    };

    BOOST_FIXTURE_TEST_SUITE(when_turned_off, when_turned_off_)
        BOOST_AUTO_TEST_CASE(is_turned_off)
        {
            BOOST_CHECK(!car.IsEngineOn());
        }
        BOOST_AUTO_TEST_CASE(cannot_repeat_turn_off)
        {
            BOOST_CHECK(!car.TurnOffEngine());
        }
        BOOST_AUTO_TEST_CASE(Unable_to_switch_to_first_gear_and_set_speed)
        {
            BOOST_CHECK_EQUAL(car.GetGear(), 0);
            BOOST_CHECK(!car.SetSpeed(5));
            BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
            BOOST_CHECK(car.SetGear(0));
        }

    BOOST_AUTO_TEST_SUITE_END()
    BOOST_AUTO_TEST_CASE(reclosing)
    {
        car.TurnOnEngine();
        BOOST_CHECK_EQUAL(car.GetGear(), 0);
        BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()