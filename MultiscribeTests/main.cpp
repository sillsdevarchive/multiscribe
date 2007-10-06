#include "UnitTest++.h"
#include "TestReporterStdout.h"

int main (int argc, char const* argv[]){
  if (argc == 1){
	return UnitTest::RunAllTests();
  }
  else {
	UnitTest::TestReporterStdout reporter;
	return UnitTest::RunAllTests(reporter, UnitTest::Test::GetTestList(), argv[1], 0);
  }
}
