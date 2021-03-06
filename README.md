![alt text](https://siodb.io/wp-content/uploads/2020/05/SIODB_Logo_Editable_half_landscape_small_logo_site.png)

## Deliver safer and faster with Siodb, a Swiss-knife database to remove database complexity

- **Performance automation:** Years of experience automated in Siodb (indexing, defragmentation, etc)
- **Easy integration in your project:** Get the simplicity of REST or the power of SQL
- **Full encryption:** Keep your data always encrypted at rest and in-transit with the safest protocols and cipher algorithms

**Current status:** Beta version (give your feedack [support@siodb.io](mailto:support@siodb.io))

## Quick Start

### Docker

```bash
docker run -p 127.0.0.1:50000:50000/tcp --name siodb siodb/siodb
```

### Cloud

[![Deploy to Hidora](https://raw.githubusercontent.com/siodb/siodb-jelastic/master/images/deploy-to-hidora.png)](https://siodb.hidora.com)

*Free Trial. Only requires an email address.*

### Linux

Get the bootstrap script and run it:

```bash
wget https://siodb.io/packages/InstallSiodb.sh
chmod u+x ./InstallSiodb.sh
sudo ./InstallSiodb.sh
```

### Connect to the instance

Connect to the Siodb instance as `siodb`:

```bash
sudo -i -u siodb siocli --user root
```

More details in [the documentation here](https://docs.siodb.io).

### Create your first database

```sql
create database myapp ;
---> Creates an encrypted database with the default cipher AES128
```

### Create your first table

```sql
use database myapp ;

create table employees ( firstname text, lastname text, salary float, hire_date timestamp) ;

insert into employees ( firstname, lastname, salary, hire_date)
values
( '马', '云', 249000.00, '1964-09-10' ),
( 'Юрий', 'Гагарин', 49000.00, '1934-03-09' ),
( 'Barack', 'Obama', 149000.00, '1961-08-04' )
;
```

### POST Request

Create a token for the `root` user:

```bash
TOKEN=$(sudo -i -u siodb siocli --user root <<< 'alter user root add token TOKEN1' | grep 'Server: token:' | awk '{print $3}')
```

Make a POST request with the `root` user and the created token:

```bash
curl -k -X POST \
-d '[
    { "firstname": "马","lastname": "云","salary": "249000.00","hire_date": "1964-09-10"},
    { "firstname": "Юрий","lastname": "Гагарин","salary": "49000.00","hire_date": "1934-03-09"},
    { "firstname": "Barack","lastname": "Obama","salary": "149000.00","hire_date": "1961-08-04"}
]' \
https://root:${TOKEN}@localhost:50443/databases/myapp/tables/employees/rows
```

**Returns:**

```json
{
	"status": 200,
	"affectedRowCount": 3,
	"trids": [1, 2, 3]
}
```

### GET Request

```bash
curl -s -k https://root:${TOKEN}@localhost:50443/databases/myapp/tables/employees/rows \
| json_pp -json_opt pretty,utf8
```

**Returns:**

```json
{
   "rows" : [
      {
         "FIRSTNAME" : "马",
         "HIRE_DATE" : "1964-09-10",
         "LASTNAME" : "云",
         "SALARY" : 249000,
         "TRID" : 1
      },
      {
         "FIRSTNAME" : "Юрий",
         "HIRE_DATE" : "1934-03-09",
         "LASTNAME" : "Гагарин",
         "SALARY" : 49000,
         "TRID" : 2
      },
      {
         "FIRSTNAME" : "Barack",
         "HIRE_DATE" : "1961-08-04",
         "LASTNAME" : "Obama",
         "SALARY" : 149000,
         "TRID" : 3
      }
   ],
   "status" : 200
}
```

## Contributing

Go to the contribution page 👉 [Here](CONTRIBUTING.md).

## Development resources

- REST API: https://docs.siodb.io/rest_api
- SQL: https://docs.siodb.io/sql_drivers

### Drivers

| Language | Link                                                   |
| -------- | :----------------------------------------------------- |
| Golang   | [Github](https://github.com/siodb/siodb-go-driver)     |
| Rust     | [Github](https://github.com/siodb/siodb-rust-driver)   |
| Java     | [Github](https://github.com/siodb/siodb-jdbc-driver)   |
| Python   | [Github](https://github.com/siodb/siodb-python-driver) |
| C++      | [Github](https://github.com/siodb/siodb-cxx-driver)    |
| .NET     | [Github](https://github.com/siodb/siodb-dotnet-driver) |

## Building Siodb

To build Siodb from the source code, please follow the guidelines according to your Linux
distribution [here](docs/dev/Build.md).

## Documentation

We write the documentation in Markdow and it is available in the folder `docs/users/docs`.
If you prefer a more user friendly format, the same documentation is
available online [here]( https://docs.siodb.io).

## Support

- Report your issue 👉 [here](https://github.com/siodb/siodb/issues/new).
- Ask a question 👉 [here](https://stackoverflow.com/questions/tagged/siodb).
- Siodb Slack space 👉 [here](https://join.slack.com/t/siodb-squad/shared_invite/zt-e766wbf9-IfH9WiGlUpmRYlwCI_28ng).

Whatever you would like to share with us, we are always prepared to listen: code@siodb.io.

## Support Siodb

Do you like this project? Tell it by clicking the star 🟊 on the top right corner of this page ☝☝

## Follow Siodb

- [Twitter](https://twitter.com/Sio_db)
- [Linkedin](https://www.linkedin.com/company/siodb)

## License

Siodb is free, and the source is available under the AGPL v3. Siodb uses
bundled dependencies for which you can find the license in the NOTICE file
in this repository's top-level directory.

## Useful References

- Official website of the project 👉 [here](https://siodb.io).
- [SQL99 Complete, Really](https://crate.io/docs/sql-99/en/latest/index.html)
- [Linux Containers](https://linuxcontainers.org/lxd/getting-started-cli/)
