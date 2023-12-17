# Registry

Sẽ có 2 loại lệnh được gửi cho client:
- Liệt kê subkey: SERVER sẽ gửi lệnh **REGISTRY** cùng với **LIST** và đường dẫn (ví dụ như là `HKEY_CURRENT_USER`, `HKEY_CURRENT_USER/System`), client sẽ trả về danh sách các subkey tương ứng
- Cú pháp mail cho hành động: REGISTRY LIST \<path\>
- Cập nhật key: SERVER sẽ gửi lệnh **REGISTRY** cùng với **UPDATE** và đường dẫn tới key, giá trị mới của key, và kiểu dữ liệu (kiểu dữ liệu thuộc 1 trong 3 loại: `REG_BINARY`, `REG_DWORD`, `REG_QWORD`)
- Cú pháp mail cho hành động: REGISTRY UPDATE \<path\> \<value\> \<type\>

### 1. Ở server (mail_handler.py)
```py
def registry_list(ip_address, full_path):
```
Chức năng: gửi các câu lệnh để liệt kê subkey với đường dẫn là `full_path` đến client, sau đó nhận về danh sách subkey.

Tham số: 
