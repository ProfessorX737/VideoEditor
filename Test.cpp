#include "Test.hpp"
#include <string>

Test::Test() {
	text = "Hello World!";
}

std::string Test::getText() {
	return text;
}
