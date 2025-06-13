# AirWatcher - Air Quality Monitoring System

## Team Information
- **Binôme n°3232**: Ikram IQDARI, Louis CARBO ESTAQUE
- **Binôme n°3235**: Stephane GRONDIN, Nour EL OUARDIGHI

## Project Overview

The AirWatcher project is developed for a government agency in charge of monitoring air quality across a large territory. Sensors installed throughout the region collect environmental data, stored in CSV files. 

## Objectives

The objective is to design a console-based application that can analyze this data to:

- **Detect malfunctioning or malicious sensors**
- **Compute and compare air quality levels**
- **Evaluate the impact of industrial air cleaners**
- **Manage and reward contributions from private individuals**
- **Ensure efficiency by measuring algorithm performance**

## Build Instructions

### Compilation
To compile the application, from the project's root, run:
```bash
make
```

### Execution
To run the application, run:
```bash
./bin/airwatcher
```

### Cleanup
To clean the build files, run:
```bash
make clean
```

## System Requirements
- C++17 compatible compiler
- Make build system
- Unix-like environment (Linux, macOS)