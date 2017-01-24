# boec

## Usage

Boec operates on the XML output from [ledger-cli](http://www.ledger-cli.org/):

```
ledger xml | boec
```

The output of the vanilla `boec` command is a simple LaTeX table, formatting
the ledger data as a journal (or "register" as ledger calls it). The table
layout is as follows:

```
| ID | Date       | Acc.Code | Details                     | Debet  | Credit |
|----|------------|----------|-----------------------------|--------|--------|
|0001|2017/01/01  |          | **Customer name**           |        |        |
|    |            |          | *Invoice #2017/003*         |        |        |
|    |            | 110101000| Balance:Accounts Receivable | 700.00 |        |
|    |            | 800305000| Results:Sales:Services      |        | 700.00 |
|----|------------|----------|-----------------------------|--------|--------|
|0002|2017/01/02  |          | **Customer name**           |        |        |
|    |            |          | *Invoice #2017/004*         |        |        |
|    |            | 110101000| Balance:Accounts Receivable | 968.00 |        |
|    |            | 800305000| Results:Sales:Services      |        | 800.00 |
|    |            | 800305000| Results:VAT:To pay          |        | 168.00 |
|----|------------|----------|-----------------------------|--------|--------|
|0003|2017/01/02  |          | **Vendor name**             |        |        |
|    |            |          | *Some book, bill #1342*     |        |        |
|    |            | 800305000| Results:Expenses:Books      |  15.00 |        |
|    |            | 800305000| Results:VAT:To recuperate   |   3.15 |        |
|    |            | 420904000| Balance:Accounts Payable    |        |  18.15 |
|----|------------|----------|-----------------------------|--------|--------|
```

Some notes on this layout and how it relates to the ledger entries:

* The ID is dynamically generated based on the amount of transactions in the
  ledger output, and always starts with 1.
* The account codes can be specified in a dictionary, located in
  `$HOME/.boecdict`. The layout of this file is quite simple, and can be
  copied from [the example file](https://github.com/flugelfoxes/boec/blob/master/samples/boecdict.sample) in this
  repository.
* "Customer name" and "Vendor name", i.e. the first line of each entry in the
  details cell, is what is called the [payee]() in ledger-cli. It is printed
  in bold in the LaTeX output.
* What is shown as "Invoice #2017/003", "Bill #1342", etc., are [notes]() in
  ledger-cli. It is printed in italics (emph) in the LaTeX output


## Installing boec

### Building from source

Clone this repository and run `make`.

### Install

Run `make install` as root (or with `sudo`).
