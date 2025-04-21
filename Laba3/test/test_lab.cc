#include <Shapes.h>
#include <gtest\gtest.h>
#include <memory>

TEST(compareSuite, baseCase) {
    Triangle tr1({ {0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f} });
    Triangle tr2({ {0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f} });
    ASSERT_TRUE(tr1 == tr2);
}

TEST(compareSuite, differentOrder) {
    Triangle tr1({ {0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f} });
    Triangle tr2({ {0.0f, 0.0f}, {2.0f, 0.0f}, {1.0f, 1.0f} });
    ASSERT_TRUE(tr1 == tr2);
}

TEST(compareSuite, failOnDifferentPoints) {
    Triangle tr1({ {0.0f, 1.0f}, {1.0f, 1.0f}, {2.0f, 0.0f} });
    Triangle tr2({ {0.0f, 0.0f}, {2.0f, 0.0f}, {1.0f, 1.0f} });
    ASSERT_FALSE(tr1 == tr2);
}

TEST(areaCalculationSuite, baseCase) {
    double answer = 4.5;
    Triangle tr({ {0.0f, 0.0f}, {3.0f, 0.0f}, {0.0f, 3.0f} });
    ASSERT_EQ(double(tr), answer);
}

TEST(centerCalculationSuite, baseCase) {
    Vertex answer;
    answer.x = answer.y = 1.0f;
    Triangle tr({ {0.0f, 0.0f}, {3.0f, 0.0f}, {0.0f, 3.0f} });
    ASSERT_EQ(tr.GetCenter(), answer);
}

TEST(polymorphicTest, baseCase) {
    double answer = 20004.5;

    auto s1 = Triangle(Triangle({ {0.0f, 0.0f}, {3.0f, 0.0f}, {0.0f, 3.0f} }));
    auto s2 = Square(Vertex{ 0.0f, 0.0f }, 100.0f);
    auto s3 = Rectangle(Vertex{ 0.0f, 0.0f }, 100.0f, 100.0f);

    std::vector<Shape*> container = {
        &s1, &s2, &s3
    };

    double result = 0.0f;
    for (auto& p : container) {
        result += p->GetArea();
    }

    ASSERT_EQ(result, answer);
}