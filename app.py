from flask import Flask, render_template, request, jsonify
import time

app = Flask(__name__)

print("🚀 Flask started (NO AI MODE)")

data_store = {
    "temperature": 30,
    "voltage": 48,
    "current": 10,
    "status": "SAFE",
    "battery": 100,
    "history": []
}

@app.route('/')
def home():
    return render_template("index.html")

@app.route('/update', methods=['POST'])
def update():
    try:
        temp = float(request.form.get('temperature', 0))
        volt = float(request.form.get('voltage', 0))
        curr = float(request.form.get('current', 0))

        # 🔥 Status logic
        if temp > 50:
            status = "DANGER"
        elif temp > 40:
            status = "WARNING"
        else:
            status = "SAFE"

        battery = max(0, 100 - (temp * 0.5 + curr * 0.3))

        data_store["temperature"] = temp
        data_store["voltage"] = volt
        data_store["current"] = curr
        data_store["status"] = status
        data_store["battery"] = battery

        data_store["history"].append({
            "time": time.strftime("%H:%M:%S"),
            "temperature": temp,
            "battery": battery
        })

        if len(data_store["history"]) > 20:
            data_store["history"].pop(0)

        return "OK"

    except Exception as e:
        print("ERROR:", e)
        return "ERROR"

@app.route('/data')
def get_data():
    return jsonify(data_store)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)