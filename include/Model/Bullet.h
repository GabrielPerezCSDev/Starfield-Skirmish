#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    // Constructor that initializes the bullet with damage and speed
    Bullet(int damage, double speed) : damage(damage), speed(speed), x(0), y(0) {}

    // Setters for x and y coordinates
    void setX(int xCord){x = xCord;};
    void setY(int yCord){y = yCord;};

    // Getters for damage, speed, and coordinates
    int getDamage() {return damage;};
    double getSpeed(){return speed;};
    int getX() const {return x;};
    int getY() const {return y;};

    void setDesign(char des) {design = des;};
    char getDesign() const {return design;};

    void setColorPairId(int id) { colorPairId = id; }
    int getColorPairId() const { return colorPairId; } // Getter for color pair ID
    int getAccumulator(){return accumulator;}
    void setAccumulator(double accum){accumulator = accum;}
    void setType(int t){type = t;}
    int getType(){return type;}

    void update(double deltaTime) {
    accumulator -= deltaTime;
    if(type == 1){ //player bullet
        while (accumulator <= 0) {
        setY(getY()-1);
        accumulator += 1.0 / getSpeed();  // Reset accumulator based on speed
        }
    }else{
        while (accumulator <= 0) {
        setY(getY()+1);
        accumulator += 1.0 / getSpeed();  // Reset accumulator based on speed
    }
    }
}

private:
    int damage;   // Damage value of the bullet
    double speed; // Speed of the bullet
    int x, y;     // Coordinates of the bullet
    char design;
    int colorPairId; // Color pair ID for ncurses
    double accumulator; 
    int type;
};

#endif // BULLET_H