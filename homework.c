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
    int size = sizeof(stations) / sizeof(*stations);
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
                        count++;
                    }
                    else if (j == lastIndex)
                    {
                        neighboringStations[count] = system.MetroLines[i].MetroStations[j - 1];
                        count++;
                    }
                    else
                    {
                        neighboringStations[count] = system.MetroLines[i].MetroStations[j - 1];
                        count++;
                        neighboringStations[count] = system.MetroLines[i].MetroStations[j + 1];
                        count++;
                    }
                }
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    MetroSystem system;
    system.count = 0;

    MetroLine line;
    strcpy(line.color, "Green");
    line.count = 0;
    addLine(&system, line);

    MetroStation station;
    strcpy(station.name, "Sogutlucesme");
    station.x = 5;
    station.y = 8;
    addStation(&line, station);

    MetroStation station1;
    strcpy(station1.name, "Kartal");
    station1.x = 6;
    station1.y = 7;
    addStation(&line, station1);

    MetroStation station2;
    strcpy(station2.name, "Samandira");
    station2.x = 12;
    station2.y = 16;
    addStation(&line, station2);

    MetroLine line1;
    strcpy(line1.color, "Blue");
    line1.count = 0;
    addLine(&system, line1);

    MetroStation station3;
    strcpy(station3.name, "Goztepe");
    station3.x = 26;
    station3.y = 4;
    addStation(&line1, station3);

    MetroLine line2;
    strcpy(line2.color, "Red");
    line2.count = 0;
    addLine(&system, line2);

    MetroStation station4;
    strcpy(station4.name, "Bostanci");
    station4.x = 5;
    station4.y = 5;
    addStation(&line2, station2);

    MetroLine line3;
    strcpy(line3.color, "Red");
    line2.count = 0;
    addLine(&system, line3);

    MetroStation station5;
    strcpy(station5.name, "Haydarpasa");
    station5.x = 16;
    station5.y = 8;
    addStation(&line3, station5);

    MetroStation neighboringStations[2];

    getNeighboringStations(system, station1, neighboringStations);
    // print each element of neighboring stations to the console
    for (int i = 0; i < 2; i++)
    {
        printf("%s\n", neighboringStations[i].name);
    }
    return 0;
}