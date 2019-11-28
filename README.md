# Find my Alcoholic

19년도 하반기 캡스톤디자인
앙 기모뤼

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

What things you need to install the software and how to install them

```
Give examples
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### MQTT를 응용한 IOT 통신 구현

컨트롤러 페이지에서 가상 스틱을 움직여 좌우 모터에 내릴 값 설정
설정한 값을 cloudmqtt broker 서버로 POST 전송을 한다.
MQTT 메시지 큐 브로커가 받은 메시지를 보트 클라이언트로 재전파
(cloudmqtt 의 메시지 브로커 서비스 이용 - 일정 금액을 지불하면 금액에 맞는 대역폭과 전송용량 제공함)
스마트폰의 테더링으로 인터넷에 연결된 보트는 지속적으로 MQTT 서버와 패킷을 주고 받으며 브로커로부터 메시지가 전달되면 해당 메시지를 파싱, 각 파트에 값을 부여함.
보트는 각 파트에 부여된 값대로 동작을 수행한다.

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags).

## Authors

* **Billie Thompson** - *Initial work* - [PurpleBooth](https://github.com/PurpleBooth)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Hat tip to anyone whose code was used
* Inspiration
* etc
