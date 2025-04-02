-- Keep a log of any SQL queries you execute as you solve the mystery.
--Find crime scene description--
SELECT
    description
FROM
    crime_scene_reports
WHERE
    MONTH = 7
    AND DAY = 28
    AND YEAR = 2023
    AND street = 'Humphrey Street';

-- Look for wittness statement from interviews--
SELECT
    *
FROM
    interviews
WHERE
    YEAR = 2023
    AND MONTH = 7
    AND DAY = 28;

-- Find thief exit details--
SELECT
    people.name,
    bakery_security_logs.activity,
    bakery_security_logs.license_plate,
    people.phone_number,
    people.passport_number
FROM
    people
    JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE
    bakery_security_logs.year = 2023
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute >= 15
    AND bakery_security_logs.minute <= 25
    AND bakery_security_logs.activity = 'exit';

-- Find people who withdraw money from ATM on Leggett Street on 28 July morning
SELECT
    people.name,
    people.phone_number,
    people.passport_number
FROM
    atm_transactions
    JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
    JOIN people ON people.id = bank_accounts.person_id
WHERE
    atm_transactions.year = 2023
    AND atm_transactions.month = 7
    AND atm_transactions.day = 28
    AND atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw';

--Find people who've talked less than 60 seconds on the day when theft happen
SELECT
    p1.name AS caller,
    phone_calls.caller,
    p2.name AS receiver,
    phone_calls.receiver,
    p2.passport_number
FROM
    phone_calls
    JOIN people p1 ON p1.phone_number = phone_calls.caller
    JOIN people p2 ON p2.phone_number = phone_calls.receiver
WHERE
    phone_calls.year = 2023
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60;

--Find out tomorrow's earliest flight from Fiftyville and its destination
SELECT
    origin_airport.full_name,
    origin_airport.city,
    destination_airport.full_name,
    destination_airport.city,
    people.name
FROM
    Flights
    JOIN passengers ON passengers.flight_id = flights.id
    JOIN people ON people.passport_number = passengers.passport_number
    JOIN airports AS origin_airport ON origin_airport.id = flights.origin_airport_id
    JOIN airports AS destination_airport ON destination_airport.id = flights.destination_airport_id
WHERE
    flights.year = 2023
    AND flights.month = 7
    AND flights.hour = 8
    AND flights.day = 29
    AND origin_airport.city = 'Fiftyville';

--Create a new table and find common name in all the previous main quiries:
--First main query
CREATE TEMPORARY TABLE temp_exit AS
SELECT
    people.name,
    bakery_security_logs.activity,
    bakery_security_logs.license_plate,
    people.phone_number,
    people.passport_number
FROM
    people
    JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE
    bakery_security_logs.year = 2023
    AND bakery_security_logs.month = 7
    AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10
    AND bakery_security_logs.minute >= 15
    AND bakery_security_logs.minute <= 25
    AND bakery_security_logs.activity = 'exit';

--Second main query
CREATE TEMPORARY TABLE temp_atm AS
SELECT
    people.name,
    people.phone_number,
    people.passport_number
FROM
    atm_transactions
    JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
    JOIN people ON people.id = bank_accounts.person_id
WHERE
    atm_transactions.year = 2023
    AND atm_transactions.month = 7
    AND atm_transactions.day = 28
    AND atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw';

--Third main query
CREATE TEMPORARY TABLE temp_calls AS
SELECT
    p1.name AS caller,
    phone_calls.caller,
    p2.name AS receiver,
    phone_calls.receiver,
    p2.passport_number
FROM
    phone_calls
    JOIN people p1 ON p1.phone_number = phone_calls.caller
    JOIN people p2 ON p2.phone_number = phone_calls.receiver
WHERE
    phone_calls.year = 2023
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60;

--Fourth main query
CREATE TEMPORARY TABLE temp_flights AS
SELECT
    origin_airport.full_name,
    origin_airport.city,
    destination_airport.full_name,
    destination_airport.city,
    people.name
FROM
    Flights
    JOIN passengers ON passengers.flight_id = flights.id
    JOIN people ON people.passport_number = passengers.passport_number
    JOIN airports AS origin_airport ON origin_airport.id = flights.origin_airport_id
    JOIN airports AS destination_airport ON destination_airport.id = flights.destination_airport_id
WHERE
    flights.year = 2023
    AND flights.month = 7
    AND flights.hour = 8
    AND flights.day = 29
    AND origin_airport.city = 'Fiftyville';

--Find the common name in all the quiries
SELECT
    temp_exit.name,
    temp_atm.name,
    temp_flights.name
FROM
    temp_exit
    JOIN temp_atm ON temp_exit.name = temp_atm.name
    JOIN temp_calls ON temp_calls.caller = temp_exit.name
    JOIN temp_flights ON temp_flights.name = temp_exit.name;
