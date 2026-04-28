import requests
import time
import logging
from telegram import Update
from telegram.ext import ApplicationBuilder, CommandHandler, ContextTypes

# === Proxy для работы ===
PROXY_URL = "socks5://127.0.0.1:10808"

# === НАСТРОЙКИ ===
BOT_TOKEN = "8324567820:AAFIpE4UWIB8o9KkWkIGaHriUwn9tFkG8hQ"
WEATHER_API_KEY = "57b663d7faa38dd3fe2e94de5d4fce65"

logging.basicConfig(
    format="%(asctime)s - %(levelname)s - %(message)s",
    level=logging.INFO
)

# === ПЛЕЙЛИСТЫ ===
SAD_PLAYLIST = [
    "🎵 Radiohead — Creep: https://youtu.be/XFkzRNyygfk",
    "🎵 Billie Eilish — when the party's over: https://youtu.be/pbMwTqkKSps",
    "🎵 The Cure — Pictures of You: https://youtu.be/XFkzRNyygfk",
]

ROCK_PLAYLIST = [
    "🎸 AC/DC — Thunderstruck: https://youtu.be/v2AC41dglnM",
    "🎸 Foo Fighters — Best of You: https://youtu.be/LnHzHNGS1WI",
    "🎸 The Killers — Mr. Brightside: https://youtu.be/gGdGFtwCNBE",
]


# === ФУНКЦИЯ ПОЛУЧЕНИЯ ПОГОДЫ ===
def get_weather(city: str) -> dict | None:
    url = "https://api.openweathermap.org/data/2.5/weather"
    params = {
        "q": city,
        "appid": WEATHER_API_KEY,
        "units": "metric",
        "lang": "ru"
    }
    response = requests.get(url, params=params)
    if response.status_code != 200:
        return None
    return response.json()


# === ФУНКЦИЯ ПРОВЕРКИ: ПАСМУРНО ЛИ? ===
def is_cloudy(weather_data: dict) -> bool:
    weather_id = weather_data["weather"][0]["id"]
    return weather_id not in (800, 801)


# === ОБРАБОТЧИК КОМАНДЫ /start ===
async def start(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text(
        "Привет! 🎵\n"
        "Я подберу музыку под погоду.\n\n"
        "Напиши: /weather Москва\n"
        "(или любой другой город)"
    )


# === ОБРАБОТЧИК КОМАНДЫ /weather ===
async def weather_music(update: Update, context: ContextTypes.DEFAULT_TYPE):
    if not context.args:
        await update.message.reply_text("Укажи город! Например: /weather Москва")
        return

    city = " ".join(context.args)
    await update.message.reply_text(f"Ищу погоду в городе {city}...")

    weather_data = get_weather(city)
    if weather_data is None:
        await update.message.reply_text(f"Не нашёл город '{city}'. Проверь название!")
        return

    description = weather_data["weather"][0]["description"]
    temp = weather_data["main"]["temp"]

    if is_cloudy(weather_data):
        playlist = SAD_PLAYLIST
        mood_text = "Пасмурно... держи грустный плейлист 🌧️"
    else:
        playlist = ROCK_PLAYLIST
        mood_text = "Отличная погода! Врубай рок! ☀️🎸"

    songs = "\n".join(playlist)
    message = (
        f"📍 {city}: {description}, {temp:.0f}°C\n\n"
        f"{mood_text}\n\n"
        f"{songs}"
    )
    await update.message.reply_text(message)


# === ЗАПУСК БОТА ===
def build_app():
    return (
        ApplicationBuilder()
        .token(BOT_TOKEN)
        .proxy(PROXY_URL)
        .get_updates_proxy(PROXY_URL)
        .read_timeout(30)
        .write_timeout(30)
        .connect_timeout(30)
        .pool_timeout(30)
        .build()
    )


if __name__ == "__main__":
    while True:
        try:
            app = build_app()
            app.add_handler(CommandHandler("start", start))
            app.add_handler(CommandHandler("weather", weather_music))

            print("Бот запущен!")
            app.run_polling()  # run_polling сам управляет event loop

        except KeyboardInterrupt:
            print("Бот остановлен.")
            break
        except Exception as e:
            print(f"Ошибка: {e}")
            print("Перезапуск через 5 секунд...")
            time.sleep(5)