# SensorCounter

The **SensorCounter** project uses two sensors to track activity in a doorway, enabling traffic counting for anyone walking in or out.

## Logic Overview

The system works by monitoring changes in sensor values. Here's the breakdown:

- **Sensor 1** (Counts people walking IN):
  - The counter increases when the sensor value changes from **0** to **1** (indicating someone walked in).
  
- **Sensor 2** (Counts people walking OUT):
  - The counter increases when the sensor value changes from **1** to **0** (indicating someone walked out).

### Example

If the sensor states are as follows:

- **IN = 1**: Increment **counterIn** by 1
- **OUT = 0**: Increment **counterOut** by 1

### Sample Data:

- **counterIn**: 30
- **counterOut**: 20

---

## Checking and Displaying the Difference

Every **30 seconds**, the difference between the two counters is checked and displayed.

### Example Calculation:

- **CounterIn(30)** and **CounterOut(20)** give a difference of **10**.
- This means **10 people are still in the room**.

---

## Updating and Displaying Today's Visits

Whenever the two counters are equal, the system updates the "Today's Visits" count:

- **When `counterIn` equals `counterOut`**:
  - Display **Today's Visits** with both counters.
  
### Example:

- **CounterIn(30)** and **CounterOut(30)** means **Today's Visits = 30**.
