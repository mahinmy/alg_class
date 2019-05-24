def coinsChange(values, money,coinsUsed):
    for cents in range(1, money + 1):
        minCoins = cents
        for value in values:
            if value <= cents:
                temp = coinsUsed[cents - value] + 1
                if temp < minCoins:
                    minCoins = temp
        coinsUsed[cents] = minCoins
        print(f'面值为：{cents}的最小硬币数目为：{coinsUsed[cents]}')


if __name__ == "__main__":
    values = [5,7]
    money = 998
    coinsUsed = {i:0 for i in range(money + 1)}
    coinsChange(values,money, coinsUsed)
