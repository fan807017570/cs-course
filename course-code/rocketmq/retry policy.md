ROCKETMQ 的重试策略

- When the consumption retry feature is enabled, the Apache RocketMQ broker resends a message when the message fails to be consumed. If the message fails to be consumed even after a specified number of retries, the broker sends the message to the dead-letter queue.

​	Trigger condition :

- A message fails to be consumed .In this case ,the consumer return the error status or the system throw the exception.
- A timeout error occurs or a message stays in a push queue  for an excessive period time.

   Behaviors:

- 