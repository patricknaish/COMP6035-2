.PHONY: allparts

allparts: buildpart1 buildpart2 buildpart3

buildall:
	@echo -ne "\nBuilding part 1... "
	@g++ -std=c++11 "Part1/part1.cpp" -o "Part1/part1"
	@echo "Built"
	@echo -ne "\nBuilding part 2... "
	@g++ -std=c++11 "Part2/part2.cpp" -o "Part2/part2"
	@echo "Built"
	@echo -ne "\nBuilding part 3... "
	@g++ -std=c++11 "Part3/part3.cpp" -o "Part3/part3"
	@echo "Built"

buildpart1:
	@echo -ne "\nBuilding part 1... "
	@g++ -std=c++11 "Part1/part1.cpp" -o "Part1/part1"
	@echo "Built"
	@echo -e "Running part 1...\n"
	@"Part1/part1"

buildpart2:
	@echo -ne "\nBuilding part 2... "
	@g++ -std=c++11 "Part2/part2.cpp" -o "Part2/part2"
	@echo "Built"
	@echo -e "Running part 2...\n"
	@"Part2/part2"

buildpart3:
	@echo -ne "\nBuilding part 3... "
	@g++ -std=c++11 "Part3/part3.cpp" -o "Part3/part3"
	@echo "Built"
	@echo -e "Running part 3...\n"
	@"Part3/part3"

clean:
	@rm -f "Part1/part1.exe" "Part2/part2.exe" "Part3/part3.exe" "Part1/part1.out" "Part2/part2.out" "Part3/part3.out"
	@echo "Cleaned"
