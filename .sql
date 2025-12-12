CREATE TABLE categories (
	id SERIAL PRIMARY KEY,
	category_name TEXT NOT NULL UNIQUE
);

CREATE TABLE dishes (
	id SERIAL PRIMARY KEY,
	name TEXT NOT NULL,
	category_id INT NOT NULL,
	FOREIGN KEY (category_id) REFERENCES categories(id),
	price DECIMAL(10,2) NOT NULL CHECK (price > 0)
);

CREATE TABLE orders (
	order_id SERIAL PRIMARY KEY,
	dish_id INT NOT NULL,
	FOREIGN KEY (dish_id) REFERENCES dishes(id),
	order_date DATE NOT NULL,
	quantity INT NOT NULL CHECK (quantity > 0),
	total_price NUMERIC(12, 2)
);

CREATE OR REPLACE FUNCTION set_total_price()
RETURNS TRIGGER AS $$
BEGIN
	NEW.total_price := NEW.quantity * (
		SELECT price FROM dishes WHERE id = NEW.dish_id
	);
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_set_total_price
BEFORE INSERT ON orders
FOR EACH ROW
EXECUTE FUNCTION set_total_price();

CREATE INDEX idx_categories_name
ON categories (category_name);

CREATE INDEX idx_orders_date
ON orders (order_date);
