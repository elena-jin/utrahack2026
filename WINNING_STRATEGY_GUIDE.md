# 🏆 UTRA HACKS 2026 - WINNING STRATEGY GUIDE
## All Prize Categories & How to Win Them

---

## 📋 TABLE OF CONTENTS
1. Overall Competition Strategy
2. Code Upload Sequence
3. Prize Category Strategies
4. Calibration Priority List
5. Time Management
6. Presentation Script
7. Emergency Troubleshooting

---

## 🎯 OVERALL COMPETITION STRATEGY

### Path Choice Decision Tree

**RED PATH (Obstacle Course)**
- ✅ Easier to complete
- ✅ Faster completion time (~2-3 min)
- ✅ Less calibration needed
- ✅ 60-second bonus achievable
- ⚠️ Must avoid obstacles perfectly

**GREEN PATH (Target Shooting)**
- ✅ Higher technical difficulty (good for "Cleanest Code" award)
- ✅ Curved ramp = bonus points
- ⚠️ Requires excellent color sensor calibration
- ⚠️ More reupload penalties
- ⚠️ Ball shooting unpredictable

**RECOMMENDED: Perfect RED path first, then attempt GREEN if time permits**

---

## 📁 CODE UPLOAD SEQUENCE

### RED PATH - 3 Uploads

**UPLOAD 1 - Start Position:**
```
File: RED_STAGE1_StartToRedEntry.ino
Mission: Box pickup → Red path → Drop box
Time: ~30-45 seconds
```

**UPLOAD 2 - First Blue Circle on Red Path:**
```
File: RED_STAGE2_ObstacleCourse.ino  
Mission: Navigate obstacles at speed
Time: ~45-60 seconds (aim for <60 for bonus!)
```

**UPLOAD 3 - End of Obstacle Course:**
```
File: RED_STAGE3_ReturnToStart.ino
Mission: Second box → Return to start
Time: ~30-45 seconds
```

**Total Time Target: 2:30 - 3:00 minutes**

### GREEN PATH - 3 Uploads

**UPLOAD 1 - Start Position:**
```
File: GREEN_STAGE1_StartToRampTop.ino
Mission: Box pickup → Green path → Curved ramp
Time: ~60-90 seconds
```

**UPLOAD 2 - Purple Circle (Reupload Point):**
```
File: GREEN_STAGE2_TargetNavigation.ino
Mission: Navigate colored rings to center
Time: ~30-45 seconds
```

**UPLOAD 3 - Black Center:**
```
File: GREEN_STAGE3_ShootAndReturn.ino
Mission: Shoot ball → Descend → Return
Time: ~60-90 seconds
```

**Total Time Target: 3:00 - 4:00 minutes**

---

## 🏅 PRIZE CATEGORY STRATEGIES

### 1st, 2nd, 3rd Place (Overall Score)
**Target: Maximum points on BOTH track and presentation**

**Track Strategy:**
- Complete RED path perfectly (safer bet)
- Aim for <60 second obstacle course (bonus 5 pts)
- Avoid all obstacle touches (full 5 pts)
- Ensure boxes fully lifted (5 pts each, not 3!)

**Expected Track Score: 45-55 / 59 points**

**Presentation Strategy:**
- Professional robot build (10/10 pts)
- Clear 3-minute presentation (10/10 pts)
- Advanced technical features (10/10 pts)
- Sustainability story (5/5 pts)
- Confident Q&A (5/5 pts)

**Expected Presentation Score: 35-40 / 40 points**

**Total Target: 80-95 / 99 points**

---

### Best Beginner Hack
**Target: Highest score among beginner teams**

**Strategy:**
- Don't overthink it - simplicity wins!
- Focus on reliability over complexity
- Complete RED path only (less risky)
- Practice presentation multiple times
- Show learning and problem-solving journey

**Key Differentiator:**
- Explain what you learned
- Show iterations and improvements
- Demonstrate understanding of concepts

---

### Cleanest Code 🎯 ← HIGH PRIORITY!
**Target: Highest score + cleanest, most readable code**

**Code Quality Checklist:**
✅ Every function has clear comment explaining purpose
✅ Descriptive variable names (not `x`, `y`, `temp`)
✅ Logical organization (setup, main, helpers, control)
✅ Consistent formatting and indentation
✅ No dead/commented-out code
✅ Constants clearly defined at top
✅ State machine structure (easy to follow)

**Your Code Already Has:**
- ✅ Clear section headers
- ✅ Descriptive function names
- ✅ Comprehensive comments
- ✅ Organized structure
- ✅ Calibration values clearly marked

**Additional Tips:**
- Add your team comments to header
- Document any calibration values you find
- Clean up any test code before submission
- Print the code and have judges review it

**Winning Formula: Good performance + Beautiful code = ROG Xbox Ally!**

---

### Best Presentation 🎤
**Target: Highest presentation score (40 points)**

**3-Minute Presentation Structure:**

**0:00-0:20 - Opening (Strong Hook)**
```
"Hi judges! We're Team [NAME], and we built [ROBOT NAME] 
to tackle the Winter Olympics challenge. Our robot combines 
speed, precision, and smart sensing to navigate obstacles 
faster than any Olympic athlete!"
```

**0:20-1:30 - Technical Explanation (Show Understanding)**
```
Key Points to Cover:
1. Path choice and why (RED = speed, GREEN = challenge)
2. Sensor systems:
   - IR sensors for line following
   - Ultrasonic for obstacle detection
   - Color sensor for path selection
3. Motor control strategy (high speed + precision turns)
4. Gripper mechanism design (secure box pickup)
5. Code structure (state machine, multiple uploads)
```

**1:30-2:15 - Challenges & Solutions (Show Problem-Solving)**
```
"Our biggest challenge was [X]. We solved it by [Y].
For example, obstacle avoidance required perfect timing,
so we implemented [strategy]. We tested [N] times and
optimized our speeds for the 60-second bonus."
```

**2:15-2:45 - Sustainability (Required Category)**
```
"We prioritized sustainability by:
- Using minimal materials from the kit
- Optimizing code for energy efficiency
- Reusing components in our mechanism design
- [Any recycled materials you used]"
```

**2:45-3:00 - Strong Closing**
```
"Our robot demonstrates that with smart engineering, 
you can achieve both speed AND precision. We're excited
to show you our run. Thank you!"
```

**Presentation Tips:**
- 👥 Assign roles: Speaker, Demo operator, Tech support
- 🎯 Practice to hit exactly 3 minutes
- 💪 Project confidence (even if nervous!)
- 👀 Make eye contact with judges
- 📊 Gesture to robot during explanation
- 😊 Smile and show enthusiasm!

---

### Best Track Course Performance 🏁
**Target: Highest track score (59 points)**

**Perfect Score Breakdown:**
- Pick up first box: 5 pts ✅
- Detect path split: 1 pt ✅
- Ramp up (curved): 4 pts ✅
- Ramp down (curved): 4 pts ✅
- Target navigation: 20 pts ✅
- Obstacle avoidance: 20 pts ✅
- Complete <60 sec: 5 pts ✅
- NO penalties: 0 pts ✅
**TOTAL: 59 / 59 points**

**Critical Success Factors:**
1. **Box Pickup** - Must be FULLY off ground (5 vs 3 pts!)
2. **Obstacle Avoidance** - Zero wheel touches (full 5 pts)
3. **Speed** - Complete course under 60 seconds (bonus 5 pts!)
4. **Reuploads** - Use purple circles wisely (only -1 pt each)
5. **Resets** - AVOID at all costs! (-5 pts each!)

**Optimization Strategy:**
- Run RED path at maximum safe speed
- Test obstacle avoidance 20+ times
- Perfect your turn calibration
- Use reuploads strategically (they're worth it!)

---

### Most Resourceful Design
**Target: Complete track with FEWEST components**

**Component Minimization Strategy:**

**Essential Components (Cannot Remove):**
- Arduino Uno ✓
- Motor driver ✓
- 2 DC motors ✓
- 4 wheels ✓
- 2 servos (claw + arm/shooter) ✓
- 2 IR sensors ✓
- Batteries ✓
- Wires ✓

**RED Path Additional:**
- 1 Ultrasonic sensor ✓
- 1 Color sensor ✓
**Component Count: ~12-15**

**GREEN Path Additional:**
- 1 Color sensor ✓ (critical!)
**Component Count: ~11-14**

**Minimization Ideas:**
1. **Skip Color Sensor?** 
   - ❌ Not recommended - lose path detection points
   
2. **Single Servo Design?**
   - ✅ Possible! Combine arm + claw into one mechanism
   - Use single servo for both lifting and gripping
   
3. **Simplified Gripper?**
   - ✅ Use cardboard "scoop" instead of servo claw
   - Passive gripper held by arm servo only
   
4. **Timer-Based Instead of Sensors?**
   - ⚠️ Risky but possible for RED path
   - Pre-program turns based on time
   - Must be perfectly consistent

**Winning Strategy:**
- Build simplified single-servo gripper
- Use minimum wires (direct connections where possible)
- Submit component list with explanation
- Show that simpler = more reliable

---

## ⚙️ CALIBRATION PRIORITY LIST

### CRITICAL (Must Calibrate)
1. **IR Sensor Threshold** - Without this, line following fails
   ```cpp
   #define LINE_THRESHOLD 500  // Test and adjust!
   ```

2. **Turn Timing** - Inaccurate turns = off course
   ```cpp
   #define TURN_90_TIME 650  // Measure actual turns!
   ```

3. **Servo Angles** - Wrong angles = dropped boxes
   ```cpp
   Claw open: 90°  // Must fit box!
   Claw close: 20°  // Must grip securely!
   ```

### IMPORTANT (Significantly Affects Score)
4. **Motor Speed Balance** - Ensure straight movement
   ```cpp
   analogWrite(MOTOR_LEFT_EN, speed);
   analogWrite(MOTOR_RIGHT_EN, speed);
   // If robot veers, adjust one motor ±10-20
   ```

5. **Color Sensor RGB Values** - Wrong colors = wrong path
   ```cpp
   Test on actual track colors!
   ```

6. **Obstacle Detection Distance** - Too close = collision
   ```cpp
   #define OBSTACLE_AVOID_DIST 12  // Test range!
   ```

### NICE TO HAVE (Fine Tuning)
7. **Speed Optimization** - Faster = more points
8. **Ramp Climbing Speed** - Balance power vs control
9. **Ball Shooter Power** - Maximize distance

---

## ⏱️ TIME MANAGEMENT (5-Minute Limit)

### Ideal Timeline - RED PATH

**0:00-0:30** Setup and Start
- Place robot at start
- Verify code uploaded
- Begin mission

**0:30-1:00** Stage 1 (30 sec)
- Pick up box
- Navigate to red path
- Drop box

**1:00-1:05** Upload Stage 2 (5 sec)
- Quick reupload
- Verify connection

**1:05-2:00** Stage 2 (55 sec)
- Obstacle course
- **Target: Complete in <60 sec for BONUS!**

**2:00-2:05** Upload Stage 3 (5 sec)

**2:05-2:45** Stage 3 (40 sec)
- Pick up second box
- Return to start

**2:45-5:00** Buffer time or GREEN path attempt

---

## 🐛 EMERGENCY TROUBLESHOOTING

### Common Issues & Quick Fixes

**Robot Won't Move**
```
1. Check battery voltage (>7V)
2. Verify motor driver connections
3. Test motors directly with multimeter
4. Check enable pins receiving PWM
```

**Line Following Erratic**
```
1. Recalibrate LINE_THRESHOLD
2. Clean IR sensor lenses
3. Adjust sensor height (5-10mm from ground)
4. Reduce speed for more stability
```

**Can't Detect Colors**
```
1. Test RGB values on actual track
2. Check sensor distance (1-2cm)
3. Ensure good lighting
4. Update thresholds in detectColor()
```

**Obstacles Not Detected**
```
1. Test ultrasonic with serial monitor
2. Increase OBSTACLE_AVOID_DIST
3. Check wiring (TRIG and ECHO)
4. Try slower approach speed
```

**Box Keeps Falling**
```
1. Adjust claw close angle (tighter grip)
2. Lift arm higher (fully clear ground)
3. Add rubber/grip material to claw
4. Reduce movement speed with box
```

**Robot Veers/Doesn't Go Straight**
```
1. Balance motor speeds
2. Check wheel alignment
3. Verify both motors same direction
4. Add motor speed compensation in code
```

---

## 🎯 WINNING MINDSET

### Things Judges Want to See:
✅ Problem-solving ability
✅ Understanding of your code
✅ Clean, organized build
✅ Confidence in presentation
✅ Teamwork and roles
✅ Learning from failures
✅ Passion and enthusiasm

### Things Judges Don't Care About:
❌ Perfect aesthetics (function > form)
❌ Complex features that don't work
❌ Excuses for what went wrong
❌ Overly technical jargon
❌ Reading from script

---

## 📊 FINAL SCORE PREDICTIONS

**Conservative Strategy (RED Path Only):**
- Track: 45-50 / 59
- Presentation: 35-38 / 40
- **Total: 80-88 / 99**
- **Placement: Top 3-5 teams**

**Aggressive Strategy (Both Paths):**
- Track: 50-55 / 59
- Presentation: 38-40 / 40
- **Total: 88-95 / 99**
- **Placement: Top 1-2 teams**

---

## 🏆 PRIZE TARGET RECOMMENDATIONS

**Primary Targets (Most Achievable):**
1. **Cleanest Code** - Your code is already excellent!
2. **Best Presentation** - Practice your script!
3. **Most Resourceful** - Minimize components!

**Secondary Targets (With Perfect Execution):**
4. **Best Track Performance** - Focus on RED path
5. **Best Beginner** - If team qualifies
6. **Top 3 Overall** - Combination of all above

---

## 🚀 FINAL CHECKLIST - DAY OF COMPETITION

### 30 Minutes Before:
- [ ] All batteries fully charged
- [ ] Backup batteries ready
- [ ] Code files on laptop + USB backup
- [ ] Tools ready (screwdriver, tape, etc.)
- [ ] Team roles assigned
- [ ] Presentation practiced
- [ ] Robot tested one final time

### 5 Minutes Before Your Run:
- [ ] Upload RED_STAGE1 code
- [ ] Verify robot at start position
- [ ] Clear claw opened, arm down
- [ ] Serial monitor working (for debugging)
- [ ] Team ready with Stage 2 & 3 files
- [ ] Timer ready

### During Run:
- [ ] One person uploads code
- [ ] One person monitors robot
- [ ] One person tracks time
- [ ] Stay calm if issues occur
- [ ] Use reuploads not resets!

---

## 💪 YOU'VE GOT THIS!

**Remember:**
- Your code is competition-ready
- Your strategy is solid
- Your team is prepared
- Confidence is key!

**Win or lose, you're learning invaluable skills.**

**Now go out there and claim those prizes! 🏆🤖**

---

*Good luck from your AI coding assistant!*
*- Claude*
