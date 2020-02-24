# Pipeline's Context class
Each module of the pipeline implement various callbacks that parse and transform an **oZ::HTTP::Request** to create an **oZ::HTTP::Response**.
Thus, the pipeline need a way to store each information though the various modules: **oZ::Context**.

## Context creation
Thanks to its oZ::Packet and oZ::Context::MetadataMap members, a context can store a lot of data about a client.
Thus, contexts should be stored in a client structure, in order to reuse it in various callbacks. It allows your server to be way more efficient in memory managment !

```C++
// Client structure
struct Client
{
	oZ::Context context {}; // Client's reusable context
};
```

## Cache handling
In this section we will see how caching can be achieved if you really wish to go for performances.
The **oZ::Context** class has a **oZ::Context::isConstant** function that tells if the current context is constant, and thus can be cached.
If some of your modules aren't supporting cache for specific HTTP methods, you can use the **oZ::Context::notConstant** function to set the constant state to false.
It's up to you to implement caching. You can accomplish in by creating a module or by handling it directly in the server.
