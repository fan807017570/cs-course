# BASE  COMPONENT OF NETTY 

- Channel	
- EventLoop
- ChannelHandler and ChannelPipeline
  1.   You can write the directly to the channel or write to ChannelHandlerContext  object  associate with a ChannelHandlerContext.
  2. Most ofter call when creating your custom handlers:
     - ChannelHanlderAdapter
     - ChannelInboundhandlerAdapter
     - ChannelOutboundHandlerAdapter
     - ChannelDuplexHandlerAdapter