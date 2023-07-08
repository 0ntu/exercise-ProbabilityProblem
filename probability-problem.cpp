#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

using namespace std;
using Coord = pair<double, double>;

std::random_device RD;
std::mt19937 gen(RD());
std::uniform_real_distribution<double> REAL_RAND(0.0, 1.0);
std::uniform_int_distribution<int> INT_RAND(0, 1);
std::bernoulli_distribution BOOL_RAND(0.5);

// Generates a coordinate that is placed randomly on either
// the TOP or BOTTOM side of the 1x1 square
//
// y coord is either 0 or 1
Coord getRandomHorizontalCoord() {
  static double x{-1};
  static double y{-1};

  x = REAL_RAND(gen);
  y = INT_RAND(gen);

  return make_pair(x, y);
}

// Generates a coordinate that is placed randomly on either
// the LEFT or RIGHT side of the 1x1 square
//
// x coord is either 0 or 1
Coord getRandomVerticalCoord() {
  static double x{-1};
  static double y{-1};

  x = INT_RAND(gen);
  y = REAL_RAND(gen);

  return make_pair(x, y);
}

// Gets a random coord on the border of a
// 1x1 square
Coord getRandomBorderCoord() {

  // Randomize getting either a Horizontal coord
  // or a vertical coord
  bool randomValue = BOOL_RAND(gen);

  if (randomValue) {
    return getRandomHorizontalCoord();
  } else {
    return getRandomVerticalCoord();
  }
}

// Returns true if distance of coordinate pair is greater than
// a specified value
bool compareLengths(const pair<Coord, Coord> &coordPair,
                    double distanceComparison) {
  auto [x, y] = coordPair;
  auto [x1, y1] = x;
  auto [x2, y2] = y;

  // Distance Formula
  if (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) > distanceComparison)
    return true;

  return false;
}

int main(int argc, char *argv[]) {
  // --- Argument Validation ---
  if (argc != 2) {
    cout << "error: This application expects 1 argument {Number of "
            "Simulations}\n";
    return EXIT_FAILURE;
  }
  // ---------------------------

  // ---------Initialize--------
  vector<pair<Coord, Coord>> data;
  long int numSimulations = atoi(argv[1]);
  data.reserve(numSimulations);
  // ---------------------------

  // ------Generate Randoms-----
  cout << "\nGenerating Random Data (" << numSimulations << " simulations)\n";

  for (long int i = 0; i < numSimulations; ++i)
    data.emplace_back(getRandomBorderCoord(), getRandomBorderCoord());

  cout << "Finished Generating Random Data...\n";
  // ---------------------------

  // ----Perform Calculations---
  cout << "Performing Comparison Calculations... \n";

  constexpr double lengthOfL = 1;

  int greaterThanDCount = 0;
  for (pair<Coord, Coord> pair : data) {
    if (compareLengths(pair, lengthOfL))
      ++greaterThanDCount;
  }
  // ---------------------------

  // ------Print Results--------
  cout << "Finished Performing Calculations... \n";
  cout << "\nStatistics:\nGreater Than D Count: " << greaterThanDCount
       << "\nTotal Simulations: " << numSimulations << "\n\n";

  cout << "Result: "
       << (static_cast<double>(greaterThanDCount) /
           static_cast<double>(numSimulations)) *
              100
       << "%\n";
  // ---------------------------

  return EXIT_SUCCESS;
}
