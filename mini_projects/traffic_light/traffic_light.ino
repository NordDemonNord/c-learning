/* 
  Имя: traffic_light.ino
  Назначение: симмулировать работу светофора для авто + пешеходов
  Автор: Nord
*/

void setup()
{

  /* Включем тактирование */
  RCC->IOPENR |= RCC_IOPENR_GPIOAEN; /* В блоке тактирования(RCC) берем конркетный регистр(IOPENR) и
                                        применяем на него маску(RCC_IOPENR_GPIOAEN),
                                        чтобы включить тактирование только для портов A */
  RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
  RCC->IOPENR |= RCC_IOPENR_GPIOCEN;

  RCC->APBENR1 |= RCC_APBENR1_TIM3EN; /* Включить тактирование TIM3 */

  /* Сбрасывание состояния портов */

  /* Светодиоды */

  GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk; /* Красный для авто. Сбрасываем сотсояние порта по умолчанию(ADC) */
  GPIOA->MODER &= ~GPIO_MODER_MODE6_Msk; /* Желтый для авто */
  GPIOA->MODER &= ~GPIO_MODER_MODE7_Msk; /* Зеленый для авто */

  GPIOC->MODER &= ~GPIO_MODER_MODE7_Msk; /* Красный для пешеходов */
  GPIOA->MODER &= ~GPIO_MODER_MODE9_Msk; /* Зеленый для пешеходов */

  /* Кнопка и зуммер */

  GPIOB->MODER &= ~GPIO_MODER_MODE10_Msk; /* Кнопка фазы перехода пешеходов */

  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD10_Msk; /* Кнопка фазы перехода пешеходов. 
                                              Сброс сотояния подтяжки */
  GPIOA->MODER &= ~GPIO_MODER_MODE12_Msk; /* Зумер, пищание во время фазы перхода пешеходов */

  /* Присваивание состояния портам */

  /* Светодиоды */

  GPIOA->MODER |= GPIO_MODER_MODE5_0; /* Красный для авто.Переводим порт в состояние выхода */
  GPIOA->MODER |= GPIO_MODER_MODE6_0; /* Желтый для авто */
  GPIOA->MODER |= GPIO_MODER_MODE7_0; /* Зелёный для авто */
  
  GPIOC->MODER |= GPIO_MODER_MODE7_0; /* Красный для пешеходов */
  GPIOA->MODER |= GPIO_MODER_MODE9_0; /* Зелёный для пешеходов */

  /* Кнопка и зуммер */

  GPIOB->PUPDR |= GPIO_PUPDR_PUPD10_0; /* Подтяжка кнопки к + */

  GPIOA->MODER |= GPIO_MODER_MODE12_0; /* Зумер, пищание во время фазы перхода пешеходов */

  /* Инициализация TIM3 */

  TIM3->PSC = 48000 - 1; /* Начальный делитель */
  TIM3->ARR = 500 - 1; /* Период */
  TIM3->EGR = TIM_EGR_UG; /* Обновляем таймер для запуска с настроенным PSC */
  TIM3->SR = ~TIM_SR_UIF; /* Сброс флага таймера */
  TIM3->CR1 |= TIM_CR1_CEN; /* Начало отсчета */

  #if 0

  /* Зажигаем все 5 светодиодов */

  GPIOA->BSRR = GPIO_BSRR_BS5; /* Красный светодиод для авто */
  GPIOA->BSRR = GPIO_BSRR_BS6; /* Желтый светодиод для авто */
  GPIOA->BSRR = GPIO_BSRR_BS7; /* Зеленый светодиод для авто */

  GPIOC->BSRR = GPIO_BSRR_BS7; /* Красный светодиод для пешеходов */
  GPIOA->BSRR = GPIO_BSRR_BS9; /* Зелёный светодиод для пешеходов */

  #endif

}

void loop()

{

  if ( ( TIM3->SR & TIM_SR_UIF ) != 0 ) /* Eсли флаг таймер поднят */

  {

      TIM3->SR = ~TIM_SR_UIF; /* Сброс флага таймера */

      if ( ( GPIOA->ODR & GPIO_ODR_OD5 ) != 0 ) /* Проверка вывода порта красного светодиода для авто */

      {

          GPIOA->BSRR = GPIO_BSRR_BR5; /* Если горит, то потушить */

      } else

      {

          GPIOA->BSRR = GPIO_BSRR_BS5; /* Иначе зажечь */

      }

  }

}
