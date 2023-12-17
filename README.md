<div align='center'>
<h1>Remote Desktop Control</h1>
</div>

## 👋🏻 Getting Started
We are from [fit@hcmus](https://fit.hcmus.edu.vn/), and this is our final project for Computer Networking course (CSC10008). 
<br/>
Our application is designed with the aim of connecting individuals by enabling users to remotely control one computer from another, incorporating features such as image transmission, data transfer, remote monitor control, establishing and managing multiple connections, ...
<br/>
The application is written in C++17. We utilize the Networking Technical Specification of ASIO for building the network architecture of the application, along with wxWidgets used for the User Interface, and handling various events
<br/>

> [!NOTE]
> Please be aware that this project is currently under active development, and feedback is welcome for any [issues](https://github.com/LongBaoCoder2/HCMUS-Project-Remote-Desktop/issues) encountered.

<details>
<summary><kbd>Table of contents</kbd></summary>

#### 

- [✨ Features](#-features)
- [⚡️ Try our app](#️-try)
- [🛳 Build from source code ](#-build)
- [🤝 Contributing](#-contributing)
- [🔗 About us](#-about-us)

####

<br/>

</details>

## ⚡️ Try our app
Get the latest version of our app by following these steps
```bash
curl -fsSL github.com/LongBaoCoder2/HCMUS-Project-Remote-Desktop/releases/latest/download/Remote-Control.zip -O
unzip -q Remote-Control.zip -d Remote-Control
```

## 🛳 Build from source code

> [!IMPORTANT]
> We utilize `CMake` for building, testing, and packaging automatically. Therefore, the initial step involves installing this tool. Ensure that your language version is C++17.


Everything has been configured and automated. Your task is to use the following script to download the necessary packages and build the project: 
```
cmake -S. -Bbuild
cmake --build build
```

This will create a directory named _build_ and create all build artifacts there. The main executable can be found in the `build/subprojects/Build/Remote_desktop` folder.
