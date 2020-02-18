# Pipeline's Context class
Each module of the pipeline implement various callbacks that parse and transform an **oZ::HTTP::Request** to create an **oZ::HTTP::Response**.
Thus, the pipeline need a way to store each information though the various modules: **oZ::Context**.

## Context creation
The context can be default created but to make it process-able, you must specify a **oZ::Packet** containing a client endpoint and its message buffer.
At this point, you can run the **oZ::Pipeline::runPipeline** function to process the context and create a response out of it.
```C++
// Callback triggered when receiving messages from clients on default HTTP port
void MyServer::onReceiveNetworkPacket(oZ::Packet &&packet)
{
	// Create a context out of a network Packet
	oZ::Context context(std::move(packet));

	// Run the pipeline with this new context and send its response to the client
	_pipeline.runPipeline(context);
	sendResponseToClient(context);
}
```

## Encryption
As you may know, HTTP uses default port 80. However, if you want to add encryption to your server exchanges, you must use the default HTTPS port 443.
Thus, the context need a way to store an encryption flag (to know if the client uses HTTPS) and an encryption key. This data is contained in the **oZ::Packet** class.

If you use openSSL for the encryption, you may need to use **Pipeline::onConnection**, **Pipeline::onDisconnection**, **IModule::onConnection** and **IModule::onDisconnection** to implement it as a standalone module.

```C++
// Callback triggered when receiving messages from clients on default HTTPS port
void MyServer::onReceiveEncryptedNetworkPacket(oZ::Packet &&packet)
{
	// Create a context out of a network Packet
	oZ::Context context(std::move(packet));

	// Set the encryption flag in the context
	context.getPacket().setEncryption(true);
	// Run the pipeline with this new context and send its response to the client
	_pipeline.runPipeline(context);
	sendResponseToClient(context);
}
```

## Cache handling
In this section we will see how caching can be achieved if you really wish to go for performances.
The **oZ::Context** class has a **oZ::Context::isConstant** function that tells if the current context is constant, and thus can be cached.
If some of your modules aren't supporting cache for specific HTTP methods, you can use the **oZ::Context::notConstant** function to set the constant state to false.
It's up to you to implement caching. You can accomplish in by creating a module or by handling it directly in the server.
