#include <cstdio>
#include <chrono>
#include <fstream>
#include <string>

#define YOLO

#define main main2
#include "main.cpp"
#undef main

int main(int argc, char * argv[])
{
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".log", "w", stdout);

	auto start_time = std::chrono::high_resolution_clock::now();
	main2(argc, argv);
	auto end_time = std::chrono::high_resolution_clock::now();

	fclose(stdin);
	fclose(stdout);

	std::fstream output(FILENAME ".log");
	std::fstream reference(FILENAME ".ans");

	if (!output.good())
	{
		fprintf(stderr, "Could not open output file: " FILENAME ".log\n");
		return 1;
	}

	if (!reference.good())
	{
		fprintf(stderr, "Could not open reference file: " FILENAME ".ans\n");
		return 1;
	}

	int line = 0;
	while (reference.good())
	{
		if (!output.good())
		{
			fprintf(stderr, "End of file in output file at line: %d\n", line);
			return 1;
		}

		std::string buf1, buf2;
		reference >> buf1;
		output >> buf2;

		if (buf1 != buf2)
		{
			fprintf(stderr, "Error at line: %d: '%s' != '%s'\n", line, buf1.c_str(), buf2.c_str());
			return 1;
		}

		++line;
	}

	if (output.good())
	{
		fprintf(stderr, "Output is longer than expected\n");
		return 1;
	}

	auto time = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count());
	fprintf(stderr, "Test passed %.2f ms\n", time / 1000);

	return 0;
}
