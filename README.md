# 一 需求分析
## 1.1 问题描述
校园交易平台，包括用户信息，商品信息和订单信息。  
用户信息包括：ID、用户名、用户密码、电话号、地址、钱包余额。商品信息包括：商品ID、商品名称、商品价格、售卖人ID、上架时间、销售状态、商品描述。订单信息包括：订单ID、商品ID、交易金额、卖家ID、买家ID。  
## 1.2 系统功能分析  
1.普通用户：首次进入校园交易平台的人，可以注册自己的用户账号，注册完成后可以使用用户名和密码登陆交易平台，也可以对自己的个人信息进行查看和修改，充值用以购买商品。  
2.买家：购买商品的用户可以查看与搜索商品，对于感兴趣的商品进行购买，在购买商品后可以查看订单，明确商品状态，也可以用来查看自己已经完成的订单信息。  
3.卖家：有闲置物品的用户可以发布商品用以售卖，在发布商品后可以对商品信息进行修改，也可以将不想售卖的商品下架，查看自己已经完成的订单信息。  
4.管理员：作为维护校园交易平台的管理员，可以查看和搜索所有商品的信息，也可以查看所有的订单信息和用户信息，对于违规用户，管理员可以删除用户，下架不合格商品，来维护一个良好的校园交易环境。  
## 1.3 系统解决方案  
### 1.3.1 功能模块设计  
开发一个集商品信息管理，买卖商品，用户管理，订单查询，商品搜索于一体的数字化贸易系统，为管理员，买家和卖家提供便捷的服务。系统可以分为四大模块：  
**普通用户**  
（1）用户注册：注册用户时，用户名不能与已有的用户名重复，注册时密码进行二次输入以保证密码输入正确。注册成功后系统会为该用户初始化一个唯一的用户ID并将用户信息存入文件。  
（2）用户登录：登陆时输入用户名和密码，通过用户文件检查用户名密码的正确性来验证用户登陆信息。  
（3）个人信息维护：登陆成功后,用户可以查看个人信息并修改密码，联系方式和地址等。也可以充值用来购买商品。  
**买家**  
（1）查看商品列表:买家通过查看商品列表操作可以看到所有在售的商品的信息(商品ID、名称、价格、上架时间、卖家ID、商品状态)以便购买。  
（2）搜索商品:支持使用名称和价格及综合(名称和价格)搜索,方便用户不同需求购买商品。  
购买商品:每个用户拥有一个钱包数额,初始数额为0,卖出则数额增加,买入则数额减少.若购买商品时钱包不足,会导致购买失败,此时可以选择在个人中心充值。  
（3）查看历史订单:买家可以查看自己购买商品的订单信息(订单ID、商品ID、交易金额、交易时间、买家ID、卖家ID)。  
（4）查看商品详细信息:买家可以通过输入商品的ID查看商品的详细信息(商品名称、商品描述、商品上架时间、卖家ID、商品状态)。  
**卖家**  
（1）发布商品:卖家通过输入商品的名称,金额以及描述来发布商品,在发布前二次确认商品信息来确保发布的商品信息无误。  
（2）查看已发布商品:卖家可以查看自己已发布的所有商品(所有状态)。  
（3）修改商品信息:通过输入商品的ID可以修改商品的价格和描述,让商品信息更加准确,若试图修改商品不存在的信息会导致修改失败。  
（4）下架商品:当商品不需要进行售卖时,卖家可以下架自己的商品。  
（5）查看历史订单:卖家可以查看自己已经卖出商品的历史订单。  
**管理员**  
（1）查看所有商品:管理员可以以列表形式输出所有的商品信息,包括在售,售出,下架状态的商品(每个商品的ID是唯一的)。  
（2）搜索商品:支持使用名称和价格以及综合(名称和价格)搜索。未搜索到商品时提示没有搜索到并返回初始页面。  
（3）查看所有订单:展示每个订单的所有信息,订单ID、商品ID、交易金额、交易时间、买家ID、卖家ID。(每个订单的ID是唯一的)  
（4）查看所有用户:管理员可以通过该操作查看用户ID,用户名,联系方式,地址和钱包余额。  
（5）删除用户:管理员通过输入用户的ID实现用户的删除,同时下架该用户发布的商品,相应的文件中同时更新。  
（6）下架商品:管理员通过输入商品ID实现商品的删除,相应文件中同时更新。  
# 二 系统设计  
## 2.1 数据设计  
### 2.1.1 用户类的设计  
该类定义了获取与修改ID、用户名、电话号码、地址、钱包余额等功能。  

             Users
- id: string  
- username: string
- password: string 
- phone: string
- address: string
- balance: string 
+ Users()   
+ Users(id: string, username: string, password: string, phone: string, address: string, balance: string)
+ setId(id: string): void  
+ setUsername(username: string): void 
+ setPassword(password: string): void
+ setPhone(phone: string): void  
+ setAddress(address: string): void 
+ setBalance(balance: string): void
+ getId(): string 
+ getUsername(): string 
+ getPassword(): string   
+ getPhone(): string  
+ getAddress(): string  
+ getBalance(): string 
### 2.1.2 商品类的设计
该类实现了获取和修改商品ID、名称、价格、描述、售卖人ID、上架时间、商品状态等功能。  

            Product
- ID: string
- name: string
- price: string  
- description: string
- sellerID: string  
- putOnTime: string   
- status: string        
  
+ Product()  
+ Product(ID: string, name: string, price: string, description: string, sellerID: string, putOnTime: string, status: string)
+ getID(): string  
+ getName(): string  
+ getPrice(): string 
+ getDescription(): string
+ getSellerID(): string  
+ getPutOnTime(): string
+ getStatus(): string
+ setID(id: string): void 
+ setName(newName: string): void
+ setPrice(newPrice: string): void
+ setDescription(desc: string): void
+ setSellerID(seller: string): void
+ setPutOnTime(time: string): void
+ setStatus(newStatus: string): void 
## 2.2 结构设计
### 2.2.1 功能模块图
<img width="866" height="1084" alt="image" src="https://github.com/user-attachments/assets/8a9ec10b-7e34-4f90-a777-041ff2861530" />
# 三 功能展示
主界面：
<img width="384" height="238" alt="image" src="https://github.com/user-attachments/assets/1b08c862-0c6d-40e5-92ea-1ce294252881" />
用户界面：
<img width="380" height="260" alt="image" src="https://github.com/user-attachments/assets/f07f1631-6306-47c9-8272-11f49324e976" />
买家界面：
<img width="400" height="278" alt="image" src="https://github.com/user-attachments/assets/af377695-6a2e-47ef-82ef-3c789740978f" />
卖家界面：
<img width="400" height="316" alt="image" src="https://github.com/user-attachments/assets/33bc7134-f4a3-4170-b203-64e38ddb91f3" />
管理员界面：
<img width="400" height="316" alt="image" src="https://github.com/user-attachments/assets/4beb411b-d689-4241-b4d8-af2b6e53b12d" />





