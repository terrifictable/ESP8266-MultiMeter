-- @block
-- Create Database `Input` Containing: id, pin and voltage columns
ALTER TABLE Input(
    id          INT PRIMARY KEY AUTO_INCREMENT,
    `time`      TIMESTAMP DEFAULT NULL ON UPDATE CURRENT_TIMESTAMP,
    pin         VARCHAR(255),
    voltage     FLOAT
);

-- @block
-- Insert new value into Input table
INSERT INTO Input(pin, voltage)
VALUES (
    "D1",
    1.5
);

-- @block
-- Display Contents of Input table
SELECT * FROM Input;

-- @block
-- REMOVE * FROM Input
DELETE FROM Input;
