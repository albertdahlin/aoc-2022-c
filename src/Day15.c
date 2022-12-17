#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "String.h"


#define push(arr, item) arr[arr##_len] = item; arr##_len += 1

typedef struct {
    int64_t x;
    int64_t y;
} Point;

typedef struct {
    int64_t from;
    int64_t to;
} Range;


typedef struct {
    Point pos;
    Point beacon;
} Sensor;

static int64_t distance(Point p1, Point p2)
{
    return labs(p1.x - p2.x) + labs(p1.y - p2.y);
}

static int64_t Sensor_radius(Sensor sensor)
{
    return distance(sensor.pos, sensor.beacon);
}

static int64_t max(int64_t a, int64_t b)
{
    return a > b ? a : b;
}


static size_t Sensor_parse(String input, Sensor *sensors)
{
    size_t sensors_len = 0;
    int64_t number[4];
    size_t numberIndex = 0;
    char *str = input.data;

    for (size_t i = 0; i < input.length; i++) {
        if (str[i] == 'Q') {
            break;
        }
        if (Char_isDigit(str[i])) {
            int64_t num = 0;
            int64_t sign = 1;
            if (str[i-1] == '-') {
                sign = -1;
            }

            for (; i < input.length && Char_isDigit(str[i]); i++) {
                num = 10 * num + str[i] - '0';
            }
            num *= sign;
            number[numberIndex] = num;

            if (numberIndex == 3) {
                Sensor sensor = {0};
                sensor.pos.x = number[0];
                sensor.pos.y = number[1];
                sensor.beacon.x = number[2];
                sensor.beacon.y = number[3];
                push(sensors, sensor);
                numberIndex = 0;
            } else {
                numberIndex += 1;
            }
        }
    }

    return sensors_len;
}

static size_t Sensor_ranges(Sensor *sensors, size_t sensors_len, int64_t y, Range *rangesOut)
{
    size_t rangesOut_len = 0;

    for (size_t i = 0; i < sensors_len; i++) {
        Sensor sensor = sensors[i];
        int64_t dy = labs(sensor.pos.y - y);
        int64_t radius = max(0, Sensor_radius(sensor) - dy);
        if (radius == 0) {
            continue;
        }
        Range range = {
            sensor.pos.x - radius,
            sensor.pos.x + radius
        };
        push(rangesOut, range);
    }

    return rangesOut_len;
}

static size_t Range_unify(Range *ranges, size_t ranges_len, Range *overlap)
{
    size_t overlap_len = 0;

    Range prev = ranges[0];

    for (size_t i = 1; i < ranges_len; i++) {
        Range range = ranges[i];

        if ((range.from - 1) <= prev.to) {
            prev.to = max(range.to, prev.to);
        } else {
            push(overlap, prev);
            prev = range;
        }
    }

    push(overlap, prev);

    return overlap_len;
}


static int ascendingByX(const void *ptr1, const void *ptr2)
{
    Point *p1 = (Point*) ptr1;
    Point *p2 = (Point*) ptr2;

    return p1->x - p2->x;
}


void Day15_solve(String input, String buffer)
{
    Sensor *sensors = (Sensor*)buffer.data;
    size_t sensors_len = Sensor_parse(input, sensors);


    // Part 1
    Range *ranges = (Range*)(sensors + sensors_len);
    int64_t y = 2e6;
    size_t ranges_len = Sensor_ranges(sensors, sensors_len, y, ranges);

    qsort(ranges, ranges_len, sizeof(Range), ascendingByX);

    Range *overlap = &ranges[ranges_len];
    size_t overlap_len = Range_unify(ranges, ranges_len, overlap);

    uint64_t part1 = 0;

    for (size_t i = 0; i < overlap_len; i++) {
        Range region = overlap[i];
        part1 += region.to - region.from;
    }


    // Part 2
    uint64_t part2 = 0;

    for (size_t y = 0; y <= 4e6; y++) {
        ranges_len = Sensor_ranges(sensors, sensors_len, y, ranges);

        qsort(ranges, ranges_len, sizeof(Range), ascendingByX);

        overlap = &ranges[ranges_len];
        overlap_len = Range_unify(ranges, ranges_len, overlap);

        if (overlap_len > 1) {
            part2 = (overlap[0].to + 1) * 4e6 + y;
            break;
        }
    }

    sprintf(buffer.data, "%12lu %12lu", part1, part2);
}



