#include <Shapes.h>
#include <gtest\gtest.h>
#include <memory>

TEST(compareSuite, baseCase) {
    Triangle<float> tr1({ {0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f} });
    Triangle<float> tr2({ {0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f} });
    ASSERT_TRUE(tr1 == tr2);
}

TEST(compareSuite, differentOrder) {
    Triangle<float> tr1({ {0.0f, 0.0f}, {1.0f, 1.0f}, {2.0f, 0.0f} });
    Triangle<float> tr2({ {0.0f, 0.0f}, {2.0f, 0.0f}, {1.0f, 1.0f} });
    ASSERT_TRUE(tr1 == tr2);
}

TEST(compareSuite, failOnDifferentPoints) {
    Triangle<float> tr1({ {0.0f, 1.0f}, {1.0f, 1.0f}, {2.0f, 0.0f} });
    Triangle<float> tr2({ {0.0f, 0.0f}, {2.0f, 0.0f}, {1.0f, 1.0f} });
    ASSERT_FALSE(tr1 == tr2);
}

TEST(areaCalculationSuite, baseCase) {
    double answer = 4.5;
    Triangle<float> tr({ {0.0f, 0.0f}, {3.0f, 0.0f}, {0.0f, 3.0f} });
    ASSERT_EQ(double(tr), answer);
}

TEST(centerCalculationSuite, baseCase) {
    Vertex<float> answer;
    answer.x = answer.y = 1.0f;
    Triangle<float> tr({ {0.0f, 0.0f}, {3.0f, 0.0f}, {0.0f, 3.0f} });
    ASSERT_EQ(tr.GetCenter(), answer);
}

TEST(polymorphicTest, baseCase) {
    double answer = 20004.5;

    auto s1 = Triangle<float>(Triangle<float>({ {0.0f, 0.0f}, {3.0f, 0.0f}, {0.0f, 3.0f} }));
    auto s2 = Square(Vertex<float>{ 0.0f, 0.0f }, 100.0f);
    auto s3 = Rectangle(Vertex<float>{ 0.0f, 0.0f }, 100.0f, 100.0f);

    std::vector<Shape<float>*> container = {
        &s1, &s2, &s3
    };

    double result = 0.0f;
    for (auto& p : container) {
        result += p->GetArea();
    }

    ASSERT_EQ(result, answer);
}