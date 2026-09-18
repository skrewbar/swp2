# 코드 설명

## `set_period`, `set_duty`

`set_period`, `set_duty`를 통해 전역에서 공통적으로 사용되는 period와 duty인 `g_period`, `g_duty`를 설정할 수 있습니다. 해당 함수에서는 최대/최솟값을 적용하는 로직도 함꼐 적용되어 있습니다.

## pwm_once

켜져 있어야 하는 시간 onTime과 꺼져 있어야 하는 시간 offTime을 계산합니다.

이때, 아두이노의 int는 16byte 정수이므로 overflow를 방지하기 위해 g_period를 long으로 캐스팅 후 계산합니다.

계산 이후 해당 시간만큼 전압을 풀고 걸어줍니다.

## triangle_fade_1s

1초 동안 삼각형 패턴으로 밝기가 변화하도록 조정합니다.

micros는 아두이노가 실행되고 나서 지난 마이크로초로, unsigned long 값을 return합니다.

다만 while 조건식에서 뺄셈을 하므로 언더플로우를 방지하기 위해 `start`의 타입을 long long으로 지정했습니다.

### while문 내부

elapsed는 함수 호출로부터 지난 시간입니다.

peak를 500,000으로 잡고 elapsed가 500,000이 되면 duty가 100이 되도록 100을 곱해서 duty에 대입합니다.

반복문마다 매번 `set_duty`를 이용해서 duty를 정하고 pwm_once를 이용해서 한 번 pulse합니다.
