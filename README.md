[![Build Status](https://travis-ci.org/MatthieuMv/openZia.svg?branch=master)](https://travis-ci.org/MatthieuMv/openZia)

[![codecov](https://codecov.io/gh/MatthieuMv/openZia/branch/master/graph/badge.svg)](https://codecov.io/gh/MatthieuMv/openZia)


[**openZia's documentation page**](https://matthieumv.github.io/openZia)

For any specific question (not convenient for an issue): matthieu.moinvaziri@epitech.eu

# open.. what ?

openZia is a C++ 17 cross-platform API for the 3rd year Epitech project **Zia**.

This library is intended to be used to build a **robust and modular HTTP server**.

# Why openZia ?

This API was designed with a strict philosophy guideline :

>  **Rigor** > **Maintenability** > **Efficiency** > **Simplicity**

Thus, openZia will exploit the best of **C++** language, avoiding risky design patterns and opting for **best practises**.

You still don't understand why you should use openZia but you want the best for your HTTP server ?
- High performance module pipeline designed for intense **multithreading** purposes;
- Intuitive module implementation;
- Easy to use HTTP classes;
- As any good piece of code on the internet, openZia is heavily unit tested;
- Simply because you want the best and the best is **openZia** !

# Dealing with the API

First of all, you should check openZia's [C++ Guideline](GUIDELINE.md) to better read its code.

## Pipeline

The API is based on a **Fixed Pipeline** that is composed of various **callbacks**.

> A fixed pipeline means that you can't change it while it is running.
> However, you can still stop and change it at run-time by reloading modules.

The **oZ::Pipeline** class abstract module loading and pipeline creation on both windows and linux. **oZ::Pipeline::loadModules** function will search dynamic libraries in the module directory provided in pipeline's constructor.

The **oZ::Context** class stores the current pipeline **state**, network client **buffer** and its **endpoint**, HTTP **request** / **response** and an **encryption key** if used by the client (to implement SSL efficiently). This class is described in details in the [Context guide](CONTEXT.md).

**oZ::Pipeline** and **oZ::Context** are intended to be used in a [State Pattern](https://en.wikipedia.org/wiki/State_pattern) where the context hold the current state and get changed while being processed.

## Modules

To implement a module you must think about **when** you need to add its **behavior** to the pipeline. Please check the detailed [Module Guide](MODULE.md) for more information.

**Here is a quick recap :**

### Initialization

Override the virtual **oZ::IModule::onRegisterCallbacks** to register your callbacks into the pipeline.

### HTTP Basics

openZia doesn't implement an HTTP parser, you must implement a specific module for that task.

You should use the different callbacks to build a **oZ::HTTP::Request** out of the network packet **oZ::Buffer**.

> When the packet is successfully parsed, use the different interpret callbacks to build your response from other modules.

### Dependencies

Each module have a callback to explicitly tell its dependencies, and another to retrieve instances to them (instead of querying them at each pipeline run), see **oZ::IModule::onRetreiveDependencies**.

### Configuration file

There are no configuration abstraction classes let you freely choose how to implement it for your needs. That said, you can easily share module with independent configuration system.

### Logging messages

Take uses of the **ILogger** interface create specific modules that, once loaded, will have his **oZ::ILogger::onLog** callback triggered each time a log is emitted.

> To emit a log, use the global helper class **oZ::Log**.

# More examples !

## Hello world
Please take a look at the very straightforward [Hello World Example](HELLO.md) file to follow a quick introduction guide.

## Compilation
If you are lost with cmake and don't know how to add the library to your project, follow this detailled [Compilation Guide](COMPILATION.md).
