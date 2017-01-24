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
| ID | Date       | Acc.Code | Details                     | Debit | Credit |
|----|------------|----------|---------------------------- |-------|--------|
|0001|2017/01/01  |          | **Customer name**           |       |        |
|    |            |          | *Invoice #2017/003*         |       |        |
|    |            | 110101000| Balance:Accounts Receivable | 700.00|        |
|    |            | 800305000| Results:Sales:Services      |       | 700.00 |
|----|------------|----------|---------------------------- |-------|--------|
|0002|2017/01/02  |          | **Customer name**           |       |        |
|    |            |          | *Invoice #2017/004*         |       |        |
|    |            | 110101000| Balance:Accounts Receivable | 968.00|        |
|    |            | 800305000| Results:Sales:Services      |       | 800.00 |
|    |            | 800305000| Results:VAT:To pay          |       | 168.00 |
|----|------------|----------|---------------------------- |-------|--------|
|0003|2017/01/02  |          | **Vendor name**             |       |        |
|    |            |          | *Some book, bill #1342*     |       |        |
|    |            | 800305000| Results:Expenses:Books      |  15.00|        |
|    |            | 800305000| Results:VAT:To recuperate   |   3.15|        |
|    |            | 420904000| Balance:Accounts Payable    |       |  18.15 |
```


## Installing boec

### Building from source

Clone this repository and run `make`.

### Install

Run `make install` as root (or with `sudo`).
