# Tên Dự Án

![Python](https://img.shields.io/badge/Python-3.10+-blue)
![License](https://img.shields.io/badge/license-MIT-green)

Mô tả ngắn gọn về dự án — làm gì, giải quyết vấn đề gì.

## Yêu cầu hệ thống

- Python >= 3.10
- pip hoặc conda

## Cài đặt

```bash
# Clone repository
git clone https://github.com/username/project.git
cd project

# Tạo môi trường ảo (khuyến nghị)
python -m venv venv
source venv/bin/activate      # Linux / macOS
venv\Scripts\activate         # Windows

# Cài đặt thư viện
pip install -r requirements.txt
```

## Cấu hình

```bash
cp .env.example .env
# Chỉnh sửa .env với các giá trị thực tế
```

## Chạy ứng dụng

```bash
python main.py
```

## Chạy kiểm thử

```bash
pytest tests/
```

## Cấu trúc thư mục

```
project/
├── main.py
├── requirements.txt
├── .env.example
├── tests/
└── src/
```
|_