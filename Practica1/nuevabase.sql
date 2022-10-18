--
-- PostgreSQL database dump
--

-- Dumped from database version 10.12 (Ubuntu 10.12-0ubuntu0.18.04.1)
-- Dumped by pg_dump version 10.12 (Ubuntu 10.12-0ubuntu0.18.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'LATIN9';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: customers; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.customers (
    customernumber integer NOT NULL,
    customername character varying(50) NOT NULL,
    contactlastname character varying(50) NOT NULL,
    contactfirstname character varying(50) NOT NULL,
    phone character varying(50) NOT NULL,
    addressline1 character varying(50) NOT NULL,
    addressline2 character varying(50) DEFAULT NULL::character varying,
    city character varying(50) NOT NULL,
    state character varying(50) DEFAULT NULL::character varying,
    postalcode character varying(15) DEFAULT NULL::character varying,
    country character varying(50) NOT NULL,
    salesrepemployeenumber integer,
    creditlimit numeric(10,2) DEFAULT NULL::numeric
);


ALTER TABLE public.customers OWNER TO alumnodb;

--
-- Name: employees; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.employees (
    employeenumber integer NOT NULL,
    lastname character varying(50) NOT NULL,
    firstname character varying(50) NOT NULL,
    extension character varying(10) NOT NULL,
    email character varying(100) NOT NULL,
    officecode character varying(10) NOT NULL,
    reportsto integer,
    jobtitle character varying(50) NOT NULL
);


ALTER TABLE public.employees OWNER TO alumnodb;

--
-- Name: offices; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.offices (
    officecode character varying(10) NOT NULL,
    city character varying(50) NOT NULL,
    phone character varying(50) NOT NULL,
    addressline1 character varying(50) NOT NULL,
    addressline2 character varying(50) DEFAULT NULL::character varying,
    state character varying(50) DEFAULT NULL::character varying,
    country character varying(50) NOT NULL,
    postalcode character varying(15) NOT NULL,
    territory character varying(10) NOT NULL
);


ALTER TABLE public.offices OWNER TO alumnodb;

--
-- Name: orderdetails; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.orderdetails (
    ordernumber integer NOT NULL,
    productcode character varying(15) NOT NULL,
    quantityordered integer NOT NULL,
    priceeach numeric(10,2) NOT NULL,
    orderlinenumber smallint NOT NULL,
	checknumber character varying(50) NOT NULL
);


ALTER TABLE public.orderdetails OWNER TO alumnodb;

--
-- Name: orders; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.orders (
    ordernumber integer NOT NULL,
    orderdate date NOT NULL,
    requireddate date NOT NULL,
    shippeddate date,
    status character varying(15) NOT NULL,
    comments text,
    customernumber integer NOT NULL
);


ALTER TABLE public.orders OWNER TO alumnodb;

--
-- Name: payments; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.payments (
    customernumber integer NOT NULL,
    checknumber character varying(50) NOT NULL,
    paymentdate date NOT NULL,
    amount numeric(10,2) NOT NULL
);


ALTER TABLE public.payments OWNER TO alumnodb;

--
-- Name: productlines; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.productlines (
    productline character varying(50) NOT NULL,
    textdescription character varying(4000) DEFAULT NULL::character varying,
    htmldescription character varying(4000),
    image character varying
);


ALTER TABLE public.productlines OWNER TO alumnodb;

--
-- Name: products; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.products (
    productcode character varying(15) NOT NULL,
    productname character varying(70) NOT NULL,
    productline character varying(50) NOT NULL,
    productscale character varying(10) NOT NULL,
    productvendor character varying(50) NOT NULL,
    productdescription text NOT NULL,
    quantityinstock smallint NOT NULL,
    buyprice numeric(10,2) NOT NULL,
    msrp numeric(10,2) NOT NULL
);


ALTER TABLE public.products OWNER TO alumnodb;

-- Optimization of the database

--
-- Name: worked_in; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.worked_in (
	employeenumber integer NOT NULL, 
	officecode character varying(10) NOT NULL
);

ALTER TABLE public.worked_in OWNER TO alumnodb;

--
-- Name: relationship; Type: TABLE; Schema: public; Owner: alumnodb
--

CREATE TABLE public.relationship (
	customernumber integer NOT NULL,
	employeenumber integer NOT NULL,
	workhere integer NOT NULL
); 

ALTER TABLE public.relationship OWNER TO alumnodb;