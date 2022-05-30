#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 10

typedef struct
{
    char name[20];
    double x, y;

} MetroStation;

typedef struct
{
    char color[20];
    MetroStation MetroStations[SIZE];
    int count;

} MetroLine;

typedef struct
{
    MetroLine MetroLines[SIZE];
    int count;

} MetroSystem;

int equals(MetroStation s1, MetroStation s2);
void addStation(MetroLine *line, MetroStation station);
int hasStation(MetroLine line, MetroStation station);
MetroStation getFirstStop(MetroLine line);
MetroStation getLastStop(MetroLine line);
MetroStation getPreviousStop(MetroLine line, MetroStation station);
MetroStation getNextStop(MetroLine line, MetroStation station);
void addLine(MetroSystem *system, MetroLine line);
void printLine(MetroLine line);
void printPath(MetroStation stations[]);
double getDistanceTravelled(MetroStation stations[]);
MetroStation findNearestStation(MetroSystem system, double x, double y);
void getNeighboringStations(MetroSystem system, MetroStation station, MetroStation neighboringStations[]);

int equals(MetroStation s1, MetroStation s2)
{
    return (strcmp(s1.name, s2.name) == 0 ? 1 : 0);
}

void addStation(MetroLine *line, MetroStation station)
{
    if (line->count < SIZE)
    {
        line->MetroStations[line->count] = station;
        line->count++;
    }
}

int hasStation(MetroLine line, MetroStation station)
{
    for (int i = 0; i < line.count; i++)
    {
        if (equals(line.MetroStations[i], station))
        {
            return 1;
        }
    }
    return 0;
}

MetroStation getFirstStop(MetroLine line)
{
    if (line.count > 0)
    {
        return line.MetroStations[0];
    }
    else
    {
        MetroStation station;
        strcpy(station.name, "NULL");
        station.x = 0;
        station.y = 0;
        return station;
    }
}

MetroStation getLastStop(MetroLine line)
{
    if (line.count > 0)
    {
        return line.MetroStations[line.count - 1];
    }
    else
    {
        MetroStation station;
        strcpy(station.name, "NULL");
        station.x = 0;
        station.y = 0;
        return station;
    }
}

MetroStation getPreviousStop(MetroLine line, MetroStation station)
{
    for (int i = 0; i < line.count; i++)
    {
        if (equals(line.MetroStations[i], station))
        {
            if (i > 0)
            {
                return line.MetroStations[i - 1];
            }
            else
            {
                MetroStation st;
                strcpy(st.name, "NULL");
                st.x = 0;
                st.y = 0;
                return st;
            }
        }
    }
    MetroStation st;
    strcpy(st.name, "NULL");
    st.x = 0;
    st.y = 0;
    return st;
}

MetroStation getNextStop(MetroLine line, MetroStation station)
{
    for (int i = 0; i < line.count; i++)
    {
        if (equals(line.MetroStations[i], station))
        {
            if (i == line.count - 1)
            {
                MetroStation st;
                strcpy(st.name, "NULL");
                st.x = 0;
                st.y = 0;
                return st;
            }
            else
            {
                return line.MetroStations[i + 1];
            }
        }
    }
    MetroStation st;
    strcpy(st.name, "NULL");
    st.x = 0;
    st.y = 0;
    return st;
}

void addLine(MetroSystem *system, MetroLine line)
{
    if (system->count < SIZE)
    {
        system->MetroLines[system->count] = line;
        system->count++;
    }
}

void printLine(MetroLine line)
{
    for (int i = 0; i < line.count; i++)
    {
        printf("%s\n", line.MetroStations[i].name);
    }
}

void printPath(MetroStation *stations)
{
    int size = sizeof(stations)/sizeof(stations[0]);
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", stations[i].name);
    }
}

double getDistanceTravelled(MetroStation *stations)
{
    double distance = 0;
    int size = sizeof(stations) / sizeof(*stations);
    if (size > 1)
    {
        for (int i = 0; i < size - 1; i++)
        {
            distance += sqrt(pow(stations[i + 1].x - stations[i].x, 2) + pow(stations[i + 1].y - stations[i].y, 2));
        }
    }
    return distance;
}

MetroStation findNearestStation(MetroSystem system, double x, double y)
{
    MetroStation station;
    strcpy(station.name, "NULL");
    station.x = 0;
    station.y = 0;
    double minDistance = 1000000;
    for (int i = 0; i < system.count; i++)
    {
        for (int j = 0; j < system.MetroLines[i].count; j++)
        {
            double distance = sqrt(pow(system.MetroLines[i].MetroStations[j].x - x, 2) + pow(system.MetroLines[i].MetroStations[j].y - y, 2));
            if (distance < minDistance)
            {
                minDistance = distance;
                station = system.MetroLines[i].MetroStations[j];
            }
        }
    }
    return station;
}

void getNeighboringStations(MetroSystem system, MetroStation station, MetroStation neighboringStations[])
{
    int count = 0;
    for (int i = 0; i < system.count; i++)
    {
        for (int j = 0; j < system.MetroLines[i].count; j++)
        {
            int lastIndex = system.MetroLines[i].count - 1;
            if (hasStation(system.MetroLines[i], station))
            {
                if (equals(system.MetroLines[i].MetroStations[j], station))
                {
                    if (j == 0)
                    {
                        neighboringStations[count] = system.MetroLines[i].MetroStations[j + 1];
                        return;
                    }
                    else if (j == lastIndex)
                    {
                        neighboringStations[count] = system.MetroLines[i].MetroStations[j - 1];
                        return;
                    }
                    else
                    {
                        neighboringStations[count++] = system.MetroLines[i].MetroStations[j - 1];
                        neighboringStations[count] = system.MetroLines[i].MetroStations[j + 1];
                        return;
                    }
                }
            }
        }
    }
}

void findPath(MetroStation start, MetroStation finish, MetroStation path[], MetroStation partialPath[])
{
}

void recursivelyFindPath(MetroStation start, MetroStation finish, MetroStation partialPath[], MetroStation bestPath[])
{
}
int main(int argc, char const *argv[])
{
    // define 3 metro lines, 9 metro stations, and an empty myPath
    MetroSystem istanbul;
    MetroLine red = {'\0'}, blue = {'\0'}, green = {'\0'};
    MetroStation s1, s2, s3, s4, s5, s6, s7, s8, s9;
    MetroStation myPath[SIZE] = {'\0'};

    strcpy(red.color, "red");
    strcpy(blue.color, "blue");
    strcpy(green.color, "green");

    strcpy(s1.name, "Haydarpasa");
    s1.x = 0;
    s1.y = 0;
    strcpy(s2.name, "Sogutlucesme");
    s2.x = 10;
    s2.y = 5;
    strcpy(s3.name, "Goztepe");
    s3.x = 20;
    s3.y = 10;
    strcpy(s4.name, "Kozyatagi");
    s4.x = 30;
    s4.y = 35;
    strcpy(s5.name, "Bostanci");
    s5.x = 45;
    s5.y = 20;
    strcpy(s6.name, "Kartal");
    s6.x = 55;
    s6.y = 20;
    strcpy(s7.name, "Samandira");
    s7.x = 60;
    s7.y = 40;
    strcpy(s8.name, "Icmeler");
    s8.x = 70;
    s8.y = 15;

    // Add several metro stations to the given metro lines.
    addStation(&red, s1);
    addStation(&red, s2);
    addStation(&red, s3);
    addStation(&red, s4);
    addStation(&red, s5);
    addStation(&red, s8);

    addStation(&blue, s2);
    addStation(&blue, s3);
    addStation(&blue, s4);
    addStation(&blue, s6);
    addStation(&blue, s7);

    addStation(&green, s2);
    addStation(&green, s3);
    addStation(&green, s5);
    addStation(&green, s6);
    addStation(&green, s8);

    // Add red, blue, green metro lines to the Istanbul metro system.
    addLine(&istanbul, red);
    addLine(&istanbul, blue);
    addLine(&istanbul, green);

    // print the content of the red, blue, green metro lines
    printLine(red);
    printf("\n");
    printLine(blue);
    printf("\n");
    printLine(green);
    printf("\n");
    getNeighboringStations(istanbul, s7, myPath);
    printPath(myPath);
    for (int i = 0; i < sizeof(myPath) / sizeof(myPath[0]); i++)
    {
        printf("%s\n", myPath[i].name);
    }
    return 0;
}