# Gửi và nhận mail
## 1. Nhận mail:
- Giao thức sử dụng: POP3
- Nhà cung cấp mail: `Microsoft Outlook`
- Sử dụng đa luồng để tối ưu hóa tác vụ.

Các hàm sử dụng:
```py
def get_mails():
```
- Công dụng: Lấy toàn bộ mail đang có trong mail box, tách lấy `email người gửi`, `tiêu đề` và `nội dung`(nếu có), đưa vào hàng đợi để luồng khác xử lý, sau đó thì xóa mail để đảm bảo không trùng lắp với thư cũ.

- Quá trình thực hiện:
    - Tạo kết nối POP3 tới server (có sử dụng SSL) 
    - Gửi Username (mail) và password để xác thực
    - Lấy số lượng mail hiện có qua lệnh `LIST`
    - Lấy thông tin từng thư qua lệnh `RETR`
    - Tách lấy thông tin
    - Xóa thư với lệnh `DELE`
    - Gửi lệnh `QUIT` ngắt kết nối

```py
def loop():
```
- Công dụng: Do tính chất của POP3 không cập nhật thư mới, cần phải reload lại sau một khoảng thời gian, nên hàm này sẽ thực hiện việc lấy thư liên tục (gọi tới hàm `get_mails()`) khi chương trình khởi chạy.

## 2. Gửi mail
- Giao thức sử dụng: SMTP
- Nhà cung cấp mail: `Microsoft Outlook`
- Sử dụng đa luồng để tối ưu hóa tác vụ.

Các hàm sử dụng:
```py
def send(to_:str, subject_:str, content_, file_name):
```
- Công dụng: Gửi thư đến địa chỉ `to_`, với tiêu đề `subject_`, nội dung `content_` và tên file `file_name` nếu nội dung cần gửi là file (file ảnh, video...)
- Tham số:
    - to_: kiểu str, là địa chỉ mail người nhận (ví dụ `abc@gmail.com`)
    - subject_: kiểu str, là tiêu đề của mail
    - content_: kiểu str hoặc bytes. Nếu là str, thực hiện gửi như văn bản bình thường. Nếu là bytes, gửi như một file với tên file là `file_name`
    - file_name: kiểu str, tên file (mặc định là "x.txt")
- Quá trình thực hiện:
    - Tạo kết nối SMTP tới server (có sử dụng TLS) 
    - Gửi Username (mail) và password để xác thực
    - Soạn thư với định dạng [`MIME multipart`](https://datatracker.ietf.org/doc/html/rfc1341)
    - Nếu thư kiểu text, attach `MIME text`
    - Nếu thư kiểu bytes, attach `MIME application` với tên file 
    - Gửi payload đến server và đóng kết nối.

```py
def safe_send(to_:str, subject_:str, content_, file_name):
```
- Công dụng: Là wrapper cho hàm `send`, thực hiện xử lý ngoại lệ: thực hiện gửi thư lại cho đến khi thành công (Do trong một số trường hợp, gửi mail quá nhanh server sẽ từ chối nên phải thực hiện lại).
- Tham số: tương tự `send`

```py
def send_threading(to_:str, subject_:str, content_, file_name = "x.txt"):
```

- Công dụng: tạo threading để gửi thư, các tham số sẽ truyền trực tiếp vào cho hàm `safe_send`. (Đây là hàm sẽ được gọi để gửi thư khi được import)