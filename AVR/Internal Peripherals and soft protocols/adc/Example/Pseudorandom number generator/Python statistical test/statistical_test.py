
import matplotlib.pyplot as plt
import pandas            as pd
import numpy             as np


# это статистический тест распределения псевдослучайных чисел функции
# ADC_Get_Random_Entropy_Value_8 бит(канал). Результат теста также действителен
# для других аналогичных функций из библиотеки adc.h.
#
# Для теста было использовано 10 000 сгенерированных значений (в файле data.csv)
#
# Результирующее распределение имеет ярко выраженные пики, поэтому эти функции
# нельзя использовать для серьезных криптографических приложений. Я рекомендую
# использовать их в сочетании с функциями srand() и rand() из
# стандартной библиотеки C в качестве начального значения инициализации
#
# this is a statistical test of the distribution of pseudorandom numbers
# of the ADC_Get_Random_Entropy_Value_8bit(channel) function. The test result
# is also valid for other similar functions from the adc.h library.
#
# 10,000 generated values were used for the test (in the data.csv file)
#
# The resulting distribution has pronounced peaks, so these functions cannot be
# used for serious cryptographic applications. I recommend using them in
# conjunction with the srand() and rand() functions from
# the C standard library as the initialization seed

data = pd.read_csv('data.csv', sep=',', header=None).to_numpy()[0]

print(f"amount of data in the histogram = {data.size}")

plt.hist(data, bins = np.arange(min(data), max(data) + 1, 1), density=True)

plt.show()
