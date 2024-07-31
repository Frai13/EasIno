# EasIno
EasIno is a library that makes easier the communication between Arduino and other devices (such as PC, Raspberry PI, etc). It defines its own communication protocol, that it is used in all of the **communication types available**:

+ Serial / UART / USART.

This common protocol allows EasIno boards to communicate with different devices regardless of the communication type used, changing only a few lines of code.

## Protocol

The protocol consists on a `HEAD` and a `TAIL` that indicates the begin and the end of the message and the data separated by `;`

As you can see in [DataCom](src/DataCom.h), data consists in two variables:

+ operation: contains the name of the message that defines its purpose.
+ args: array that contains the arguments of the operation. The maximum number of arguments is defined in `ARRAY_LENGTH` at [DataCom](src/DataCom.h).

Example of BuiltIn operation VERSION request:
> EINO::VERSION;::END


## BuiltIn operations
There are some operations with a predefined response, and can not be processed
by user.

### VERSION
Returns the EasIno version uploaded in the board.

Request:
> EINO::VERSION;::END

Response example:
> EINO::VERSION;v1.0.0;;;;;::END

### PING
Retrieves PING, proving that communication state is OK.

Request:
> EINO::PING;::END

Response example:
> EINO::PING;;;;;;::END

## APIs
EasIno can not only be used as it is, sending and receiving data using the defined protocol but also APIs can be used, which help the user interact with an EasIno embedded board. The currently **available APIs** are:

+ [C# API](https://github.com/Frai13/EasInoCSharpAPI).
+ [Python API](https://github.com/Frai13/easino-py).

## RobotTests
Robot tests are performed before launching a new release: [repo](https://github.com/Frai13/EasInoRobotTests).

## Examples
Here you can find some Arduino examples. Visit [examples](examples) for more.


