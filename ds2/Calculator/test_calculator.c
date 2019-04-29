/*******************************************************************************
* NAME: stack calculator                                                       *
*                                                                              *
* AUTHOR: Yaakov Sidikman                                                      *
* DATE UPDATED:  17.12.18                                                      *
*******************************************************************************/

#include "test.h"
#include "calculator.h"
#include <math.h> /*pow*/

/******************************************************************************/
TestResult TestPower()
{
	status result_status = SUCCESS;
    double expected_result = 3.1 * (pow(4,pow(5.3,2)))  - 4 * (-3.2);
    char *expression = "3.1 * (4 ^ 5.3 ^ 2) - 4 * (-3.2)";

	REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

TestResult TestIllegalInputs()
{
    status result_status = SUCCESS;
    char *expressions[] = {"*3.2", "3.2*", "1+2)", "1+(2+3"};
    size_t number_of_expressions = 4;
    size_t i = 0;

    for (i = 0; i < number_of_expressions; ++i)
    {
        result_status = SUCCESS;
        CalculateExpression(expressions[i], &result_status);
        REQUIRE(result_status == FAIL);
    }

	return (TEST_PASS);
}

TestResult TestSpaces()
{
    status result_status = SUCCESS;
    double expected_result = 3.1 * (4 + 5.3 / 2)  - 4 * (-3.2);
    char *expression = "3.1 * (4 + 5.3 / 2)  - 4 * (-3.2)";

	REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

TestResult TestExplicitSigns()
{
    status result_status = SUCCESS;
    double expected_result = +3.1*(+4+5.3/-2)-4*(-3.2);
    char *expression = "+3.1*(+4+5.3/-2)-4*(-3.2)";

    REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

TestResult TestOpsAfterParenthesis()
{
    status result_status = SUCCESS;
    double expected_result = 3.1*(4+5.3/2)-4*3.2;
    char *expression = "3.1*(4+5.3/2)-4*3.2";

    REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

TestResult TestMultipleParenthesis()
{
    status result_status = SUCCESS;
    double expected_result = 3.1*(((4+5.3/2)));
    char *expression = "3.1*(((4+5.3/2)))";

    REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

TestResult TestParenthesis()
{
    status result_status = SUCCESS;
    double expected_result = 3.1*(4+5.3/2);
    char *expression = "3.1*(4+5.3/2)";

    REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

TestResult TestMultipleOperationsMixedPrecedence()
{
    status result_status = SUCCESS;
    double expected_result = 3.1-4*5.3+2;
    char *expression = "3.1-4*5.3+2";

    REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

TestResult TestDifferentPrecedence()
{
    status result_status = SUCCESS;
    double expected_result = 3.1*4+5.3;
    char *expression = "3.1*4+5.3";

    REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

TestResult TestSamePrecedence()
{
    status result_status = SUCCESS;
    double expected_result = 3.1+4+5.3;
    char *expression = "3.1+4+5.3";

    REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

TestResult TestSimpleExpression()
{
    status result_status = SUCCESS;
    double expected_result = 3.1*4;
    char *expression = "3.1*4";

    REQUIRE(expected_result == CalculateExpression(expression, &result_status));
    REQUIRE(result_status == SUCCESS);

	return (TEST_PASS);
}

int main()
{
	RUN_TEST(TestSimpleExpression);
	RUN_TEST(TestDifferentPrecedence);
	RUN_TEST(TestSamePrecedence);
	RUN_TEST(TestMultipleOperationsMixedPrecedence);
	RUN_TEST(TestParenthesis);
	RUN_TEST(TestMultipleParenthesis);
    RUN_TEST(TestOpsAfterParenthesis);
    RUN_TEST(TestExplicitSigns);
    RUN_TEST(TestSpaces);
    RUN_TEST(TestIllegalInputs);
	RUN_TEST(TestPower);

	return (0);
}
