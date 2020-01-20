[![Build Status](https://travis-ci.org/MatthieuMv/openZia.svg?branch=master)](https://travis-ci.org/MatthieuMv/openZia)
[![codecov](https://codecov.io/gh/MatthieuMv/openZia/branch/master/graph/badge.svg)](https://codecov.io/gh/MatthieuMv/openZia)

# open.. what ?
openZia is a C++ 17 cross-platform API for the 3rd year Epitech project **Zia**.
This library is intended to be used to build a **robust and modular HTTP server**.

# Why openZia ?
This API was designed with a strict philosophy guideline :

> **Rigor** > **Maintenability** > **Efficiency** > **Simplicity**

Thus, openZia will exploit the best of **C++** language, avoiding risky design patterns and opting for **best practises**.

You still don't understand why you should use openZia but you want the best for your HTTP server ?
- High performance module pipeline designed for intense **multithreading** purposes;
- Intuitive module implementation;
- Easy to use HTTP classes;
- As any good piece of code on the internet, openZia is heavily unit tested;
- Simply because you want the best and the best is **openZia** !

# Dealing with the API
First of all, you should check openZia's [C++ Guideline](GUIDELINE.md) to better read its code.

The API is based on a **Fixed Pipeline** that is composed of various **callbacks**.
> A fixed pipeline means that you can't change it while it is running.
> However, you can change it at runtime if you need to reload modules.

The **oZ::Pipeline** class abstract module loading and pipeline creation on both windows and linux.
**oZ::Context** is the class used to process any HTTP request into the pipeline.
**oZ::Pipeline** and **oZ::Context** are intended to be used in a [State Pattern](https://en.wikipedia.org/wiki/State_pattern) where the context hold the current state and get changed while being processed.

To implement a module you must think about **when** you need to add its **behavior** to the pipeline.
> Override the virtual **oZ::IModule::onRegisterCallbacks** to register your callbacks.

Logging messages:
> Take uses of the **ILogger** interface create specific modules that, once loaded, will have his **oZ::ILogger::onLog** callback triggered each time a log is emited.
> To emit a log, use the global helper class **oZ::Log**.

Dependencies handling:
> Each module have a callback to explicitly tell its dependencies, and another to retreive instances to them (instead of querying them at each pipeline run), see **oZ::IModule::onRetreiveDependencies**

There are no configuration abstraction classes let you freely choose how to implement it for your needs.

Please take a look at the very straightforward [Hello World Example](HELLO.md) file to follow a quick introduction guide.
