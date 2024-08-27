#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double monteCarloCircleArea(int totalPoints, double radius);

int main() {
    int totalPoints;
    double radius;

    printf("Enter the radius of the circle: ");
    scanf("%lf", &radius);

    printf("Enter the total number of random points to generate: ");
    scanf("%d", &totalPoints);

    double estimatedArea = monteCarloCircleArea(totalPoints, radius);

    printf("Estimated area of the circle: %lf\n", estimatedArea);

    return 0;
}

double monteCarloCircleArea(int totalPoints, double radius) {
    int pointsInsideCircle = 0;
    double x, y;

    srand(time(NULL));

    for (int i = 0; i < totalPoints; i++) {
        x = (double)rand() / RAND_MAX * (2 * radius) - radius;
        y = (double)rand() / RAND_MAX * (2 * radius) - radius;

        if (x * x + y * y <= radius * radius) {
            pointsInsideCircle++;
        }
    }

    double squareArea = (2 * radius) * (2 * radius);
    double circleArea = ((double)pointsInsideCircle / totalPoints) * squareArea;

    return circleArea;
}