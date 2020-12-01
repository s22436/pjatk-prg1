/*
 * A reverse-polish notation calculator.
 */

#include <s22436/RPN_calculator.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>


static auto pop_top(std::stack<double>& stack) -> double
{
    if (stack.empty()) {
        throw std::logic_error{"empty stack"};
    }
    auto element = std::move(stack.top());
    stack.pop();
    return element;
}


namespace student { namespace rpn_calculator {
Element::~Element()
{}

Literal::Literal(double const v) : value{v}
{}
auto Literal::evaluate(stack_type& stack) const -> void
{
    stack.push(value);
}

auto Print::evaluate(stack_type& stack) const -> void
{
    std::cout << stack.top() << "\n";
}

auto Addition::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for +"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a + b);
}
auto Subtraction::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for -"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a - b);
}
auto Multiplication::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for *"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a * b);
}
auto Division::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for /"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a / b);
}
auto Integer_Division::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for //"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(static_cast<int>(a / b));
}
auto Modulus::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for %"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(std::fmod(a, b));
}
auto Exponentiation::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for **"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(std::pow(a, b));
}
auto Square_Root::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 1) {
        throw std::logic_error{"not enough operands for sqrt"};
    }
    auto const a = pop_top(stack);
    stack.push(std::sqrt(a));
}
auto factorial(int a) -> int
{
    if (a < 1) {
        throw std::logic_error{"Factorial cannot be negative"};
    }
    if (a == 1) {
        return 1;
    }
    return a * factorial(a - 1);
}
auto Factorial::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 1) {
        throw std::logic_error{"not enough operands for !"};
    }
    auto const a = pop_top(stack);
    stack.push(factorial(static_cast<int>(a)));
}

Calculator::Calculator(stack_type s) : stack{std::move(s)}
{}

auto Calculator::push(std::unique_ptr<Element> op) -> void
{
    ops.push(std::move(op));
}

// FIXME implement Calculator::push(std::string)

auto Calculator::evaluate() -> void
{
    while (not ops.empty()) {
        auto op = std::move(ops.front());
        ops.pop();

        op->evaluate(stack);
    }
}
}}  // namespace student::rpn_calculator


auto make_args(int argc, char* argv[], bool const with_exec = false)
    -> std::vector<std::string>
{
    auto args           = std::vector<std::string>{};
    auto const offset   = static_cast<size_t>(not with_exec);
    auto const copySize = static_cast<long unsigned int>(argc) - offset;
    std::copy_n(argv + offset, copySize, std::back_inserter(args));
    return args;
}

auto main(int argc, char* argv[]) -> int
{
    using student::rpn_calculator::Calculator;
    auto calculator = Calculator{};

    for (auto const& each : make_args(argc, argv)) {
        try {
            using student::rpn_calculator::Addition;
            using student::rpn_calculator::Division;
            using student::rpn_calculator::Exponentiation;
            using student::rpn_calculator::Factorial;
            using student::rpn_calculator::Integer_Division;
            using student::rpn_calculator::Literal;
            using student::rpn_calculator::Modulus;
            using student::rpn_calculator::Multiplication;
            using student::rpn_calculator::Print;
            using student::rpn_calculator::Square_Root;
            using student::rpn_calculator::Subtraction;

            if (each == "p") {
                calculator.push(std::make_unique<Print>());
            } else if (each == "+") {
                calculator.push(std::make_unique<Addition>());
            } else if (each == "-") {
                calculator.push(std::make_unique<Subtraction>());
            } else if (each == "*") {
                calculator.push(std::make_unique<Multiplication>());
            } else if (each == "/") {
                calculator.push(std::make_unique<Division>());
            } else if (each == "//") {
                calculator.push(std::make_unique<Integer_Division>());
            } else if (each == "%") {
                calculator.push(std::make_unique<Modulus>());
            } else if (each == "**") {
                calculator.push(std::make_unique<Exponentiation>());
            } else if (each == "sqrt") {
                calculator.push(std::make_unique<Square_Root>());
            } else if (each == "!") {
                calculator.push(std::make_unique<Factorial>());
            } else {
                calculator.push(std::make_unique<Literal>(std::stod(each)));
            }
        } catch (std::logic_error const& e) {
            std::cerr << "error: " << each << ": " << e.what() << "\n";
        }
    }

    try {
        calculator.evaluate();
    } catch (std::logic_error const& e) {
        std::cerr << "error: during evaluation: " << e.what() << "\n";
    }

    return 0;
}
