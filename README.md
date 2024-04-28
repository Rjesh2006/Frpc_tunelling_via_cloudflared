*first understand that what is frpc tunneling is :--⏬*
  - *FRPC tunneling is a method of securely exposing services from a local network to the internet by creating a tunnel between a local machine and a remote server. It allows you to access local services from 
     anywhere without compromising security.*


# Frpc_tunelling_via_cloudflared
  - cloudflared: *Cloudflared is a tool by Cloudflare for creating secure tunnels between a user's network and Cloudflare's network. It helps bypass restrictions, enhances security, and allows secure access to 
               internal resources from anywhere on the internet.*
 - *Frpc----tunneling through     Cloud_Flared*
    - *The commmand is for (windows cmd) its a simple proccess here:--
    ```
    winget install --id Cloudflare.cloudflare
    ```
  
  - *check the the version if cloudflared is sucessfuly installed :⏬
   ```
   cloudflared --version
   ```

 ```
  cloudflared tunnel --url http://localhost:3000
 ```
**Here's what each part of the command does:**

- *cloudflared tunnel: Initiates the Cloudflare tunneling service.*
*--url http://localhost:3000: Specifies the URL to which traffic should be forwarded through the tunnel. In this case, it's http://localhost:3000, meaning traffic directed to localhost on port 3000 of your local 
  machine will be tunneled.*
- *This command is useful when you want to expose a local service running on your machine (localhost:3000 in this case) to the internet via Cloudflare's network, enabling access to the service from anywhere with 
   enhanced security and performance provided by Cloudflare.*
  
  - *interface:--*
  - ![Screenshot 2024-04-28 230928](https://github.com/Rjesh2006/Frpc_tunelling_via_cloudflared/assets/143868643/9154fcda-8d38-461a-b025-fe675aeaaf51)
  - ![Screenshot 2024-04-28 230952](https://github.com/Rjesh2006/Frpc_tunelling_via_cloudflared/assets/143868643/a56cee5f-f3da-4e0e-a96f-025fb8c1e07b)
  - ![Screenshot 2024-04-28 231057](https://github.com/Rjesh2006/Frpc_tunelling_via_cloudflared/assets/143868643/a42cf638-8098-4e8d-a836-6a6bb2f74186)
  - ![image](https://github.com/Rjesh2006/Frpc_tunelling_via_cloudflared/assets/143868643/5ad53fb2-d1c4-4d9f-979f-c16bb1c3979a)






***NOTE--📕*** 
*whenever you will write this commands (  cloudflared tunnel --url http://localhost:3000) it will give u a temporary **Domain name** which will work as as a real domain name but the condition is your localhost server should be at running state so that the temporary (Domain name ) will forward all request to ur localhot server then other user can acess ur  web -application.*

  
