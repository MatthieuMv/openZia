# Hello World example
As the pipeline is already implemented, you will not need a lot of work to get a first "Hello World" example running (meaning more time to develop great modules !).

*Please note that this example is very straightforward and not using advantages of a multithreaded server.*

I assume you have already setup your sever basic's routine (listen, accept, read ...).
Let's say you have a class **Server**.
```C++
#include <openZia/Pipeline.hpp>
class Server {
public:
	// Set the pipeline module and configuration paths and load modules
	Server(void) : _pipeline("ModuleDir", "ConfigDir") {
		_pipeline.loadModules();
	}

	/* ... Your routines functions ... */

private:
	/* ... Your members ... */
	Pipeline _pipeline; // Pipeline loads module

	// Callback when server accept a new client
	void onClientConnected(const oZ::FileDescriptor fd, const oZ::Endpoit endpoint, bool useEncryption) {
		_pipeline.onConnection(fd, endpoint, useEncryption);
	}

	// Callback when server receive disconnection
	void onClientDisconnected(const oZ::FileDescriptor fd, const oZ::Endpoit endpoint) {
		_pipeline.onDisconnection(fd, endpoint);
	}

	// Callback when server receives a message
	void onPacketReceived(const oZ::FileDescriptor fd, oZ::ByteArray &&buffer, const oZ::Endpoint endpoint) {
		oZ::Context context(oZ::Packet(std::move(buffer), endpoint, fd));
		_pipeline.runPipeline(context);
		sendResponseToClient(context);
	}

	// Send the HTTP response to the client
	void sendResponseToClient(const Context &context) {
		/* You may use the following methods:
			context.hasError() // Fast error checking
			context.getEndpoint() // Get the endpoint of target client
			context.getResponse() // Get the response result of the pipeline
		*/
	}
};
```

Now you need to create your first module. Let's create two of them as a demonstration of dependency handling :
```C++
/* --- Hello.hpp --- */
#pragma once

#include <iostream>

#include <openZia/IModule.hpp>
#include <openZia/Pipeline.hpp> // Not defined in IModule.hpp

class Hello : public oZ::IModule
{
public:
	Hello(void) = default;
	virtual ~Hello(void) = default;

	virtual const char *getName(void) const { return "Hello"; }
	virtual Dependencies getDependencies(void) const noexcept { return { "World" }; }

	virtual void onConnection(const FileDescriptor fd, const Endpoint endpoint, const bool useEncryption) {
		std::cout << "New client connected: " << endpoint.getAdrress() << std::endl;
	}

	virtual void onDisconnection(const FileDescriptor fd, const Endpoint endpoint, const bool useEncryption) {
		std::cout << "Client diconnected: " << endpoint.getAdrress() << std::endl;
	}

	// Register your callback to the pipeline
	virtual void onRegisterCallbacks(oZ::Pipeline &pipeline) {
		pipeline.registerCallback(
			oZ::State::Interpret, // Call at response creation time
			oZ::Priority::Medium + 1, // With medium priority but higher than 'World' module
			this, &Hello::onInterpret // Member function style
		);
	}

private:
	bool onInterpret(oZ::Context &context) {
		oZ::Log(oZ::Information) << "Module 'Hello' wrote successfully its message";
		context.getResponse().getHeader().set("Content-Type", "text/plain");
		context.getResponse().getBody() += "Hello";
		return true;
	}
};

/* --- Hello.cpp --- */
#include "Hello.hpp"

OPEN_ZIA_MAKE_ENTRY_POINT(Hello);
```

```C++
/* --- World.hpp --- */
#pragma once

#include <openZia/IModule.hpp>
#include <openZia/Pipeline.hpp> // Not defined in IModule.hpp

// Second module 'World'
class World : public oZ::IModule
{
public:
	World(void) = default;
	virtual ~World(void) = default;

	virtual const char *getName(void) const { return "World"; }
	virtual Dependencies getDependencies(void) const noexcept { return { "Hello" }; }

	// Register your callback to the pipeline
	virtual void onRegisterCallbacks(oZ::Pipeline &pipeline) {
		pipeline.registerCallback(
			oZ::State::Interpret, // Call at response creation time
			oZ::Priority::Medium, // With medium priority
			[](oZ::Context &context) { // Lambda function style
				context.getResponse().getBody() += " World";
				return true;
			}
		);
	}

	virtual void onLoadConfigurationFile(const std::string &directory) {
		/* Load module's configuration if needed, using your own configuration loader */
	}
};

/* --- World.cpp --- */
#include "World.hpp"

OPEN_ZIA_MAKE_ENTRY_POINT(World);
```
