# ☁️ ThingSpeak Cloud Setup Guide

ThingSpeak is a free IoT analytics platform by MathWorks that lets you collect, visualize, and analyze data from your IoT devices.

---

## Step 1 — Create a ThingSpeak Account

1. Go to: https://thingspeak.com
2. Click **Sign Up** (top right)
3. Create a free account using your email
4. Verify your email address

---

## Step 2 — Create a New Channel

1. After logging in, click **Channels → My Channels**
2. Click **New Channel**
3. Fill in the details:

| Field | Value |
|---|---|
| **Name** | Smart City Noise Monitor |
| **Description** | Real-time noise level monitoring using Arduino and KY-038 |
| **Field 1 Name** | Noise Level |
| **Tags** | IoT, Arduino, Noise, Smart City |

4. Click **Save Channel**

---

## Step 3 — Get Your API Key

1. After saving, go to the **API Keys** tab of your channel
2. Copy the **Write API Key** — it looks like: `ABCDEFGH12345678`
3. Paste it in `noise_monitor.ino`:

```cpp
const String THINGSPEAK_API_KEY = "ABCDEFGH12345678";  // ← Your key here
```

---

## Step 4 — View Your Channel

Your channel URL will be:
```
https://thingspeak.com/channels/YOUR_CHANNEL_ID
```

You'll see a live updating graph of Field 1 (Noise Level) as data comes in from your Arduino.

---

## Step 5 — Customize the Dashboard

On your ThingSpeak channel page, click **Add Widgets** to customize your dashboard with:

- **Line Chart** — View noise level over time
- **Gauge** — Show current noise level
- **Numeric Display** — Show latest value
- **Alerts** — Send email when noise exceeds a limit (ThingSpeak React)

---

## ThingSpeak Limits (Free Plan)

| Feature | Limit |
|---|---|
| Channels | 4 |
| Messages per day | 8,200 |
| Update interval | Minimum **15 seconds** |
| Data storage | 1 year |
| API calls per day | Unlimited (read) |

> ⚠️ This is why `uploadInterval = 15` in the code — ThingSpeak rejects faster updates on free accounts.

---

## ThingSpeak React — Automatic Email Alerts

You can configure ThingSpeak to send you an **email alert** when noise exceeds a level:

1. Go to **Apps → React** on ThingSpeak
2. Click **New React**
3. Set:
   - **Condition**: Field 1 > 500 (your threshold)
   - **Action**: Send Email
   - **Email**: Your email address
   - **Message**: "Alert: High noise detected! Level: %%channel_XXXX_field_1%%"
4. Save

Now ThingSpeak will email you automatically when noise is too high!

---

## Viewing Data via API

You can also fetch your channel data programmatically:

**Latest value:**
```
https://api.thingspeak.com/channels/YOUR_CHANNEL_ID/fields/1/last.json
```

**Last 100 readings:**
```
https://api.thingspeak.com/channels/YOUR_CHANNEL_ID/fields/1.json?results=100
```

**Date range:**
```
https://api.thingspeak.com/channels/YOUR_CHANNEL_ID/fields/1.json?start=2024-01-01%2000:00:00&end=2024-01-31%2023:59:59
```

---

## MATLAB Analysis (Advanced)

ThingSpeak also provides **MATLAB Online** for analyzing your data:

```matlab
% Read data from your channel
data = thingSpeakRead(YOUR_CHANNEL_ID, 'Fields', 1, 'NumPoints', 100);

% Plot the data
plot(data)
title('Noise Level Over Time')
ylabel('ADC Value (0-1023)')
xlabel('Reading Number')
```

This is available directly on ThingSpeak under **Apps → MATLAB Analysis**.
