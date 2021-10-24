#include "lesson1.hxx"
#include <gtest/gtest.h>

class TBook : testing::Test
{
protected:
    PhoneBook* book;
    void       SetUp() override
    {
        std::stringstream src_test;
        src_test << "Ivan Selen Sergeevich 375 29 6588999 -\n"
                 << "Igor Sebsaden - 7 901 3632955 16\n";
        book = new PhoneBook(src_test);
    }
    void TearDown() override { delete book; }
};

TEST_F(TBook, GetPhoneNumber)
{

    std::string last_name = "Ivanov";
    auto        answer    = book->GetPhoneNumber(last_name);
    EXPECT_EQ(std::get<0>(answer), "entry not found");
}
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
