<img src="https://i.imgur.com/AluZXjA.png" alt="BeHero logo" width=150px >

# BeHeroCoin Setup Guide (Ubuntu 16.04)
This guide will assist you in setting up a BeHeroCoin Masternode on a Linux Server running Ubuntu 16.04. (Use at your own risk)

If you require further assistance contact the support team [Discord](https://discord.gg/tCzJs5G)
***
## Requirements
1. **5000 BeHeroCoin coins.**
2. **A Vultr VPS running Linux Ubuntu 16.04.**
3. **A Windows or Mac local wallet.**
4. **An SSH client such as [Bitvise](https://dl.bitvise.com/BvSshClient-Inst.exe)**
***
## Contents
* **Section A**: Creating the VPS within [Vultr](https://www.vultr.com/?ref=7371462).
* **Section B**: Downloading and installing Bitvise.
* **Section C**: Connecting to the VPS and installing the MN wallet via Bitvise.
* **Section D**: Preparing the local wallet.
* **Section E**: Connecting & Starting the masternode.
***

## Section A: Creating the VPS within [Vultr](https://www.vultr.com/?ref=7371462)
***Step 1***
* Register at [Vultr](https://www.vultr.com/?ref=7371462)
***

***Step 2***
* After you have added funds to your account go [here](https://my.vultr.com/deploy/) to create your Server
***

***Step 3***
* Choose a server location (preferably somewhere close to you)
![Example-Location](https://i.imgur.com/yrqBp2H.png)
***

***Step 4***
* Choose a server type: Ubuntu 16.04
![Example-OS](https://i.imgur.com/aSMqHUK.png)
***

***Step 5***
* Choose a server size: $3.5/mo will be fine
![Example-OS](https://i.imgur.com/onsDLi0.png)
***

***Step 6***
* Set a Server Hostname & Label (name it whatever you want)
![Example-hostname](https://i.imgur.com/Lgpk09r.png)
***

***Step 7***
* Click "Deploy now"

![Example-Deploy](https://i.imgur.com/4qpYuH0.png)
***


## Section B: Downloading and installing BitVise.

***Step 1***
* Download Bitvise [here](https://dl.bitvise.com/BvSshClient-Inst.exe)
***

***Step 2***
* Select the correct installer depending upon your operating system. Then follow the install instructions.

![Example-PuttyInstaller](https://i.imgur.com/yF3694G.png)
***


## Section C: Connecting to the VPS & Installing the MN script via Bitvise.

***Step 1***
* Copy your VPS IP (you can find this by going to the server tab within Vultr and clicking on your server.
![Example-Vultr](https://i.imgur.com/FsTNYHF.png)
***

***Step 2***
* Open the bitvise application and fill in the "Hostname" box with the IP of your VPS then click "Open"
![Example-PuttyInstaller](https://i.imgur.com/OgUH4X3.png)
***

***Step 3***
* Once you have clicked open it will open a security alert (click yes).  
***


***Step 4***
* Type "root" as the login/username then press enter

![Example-Root](https://i.imgur.com/KttHwsx.png)
***

***Step 5***
* Copy the root password from the VULTR server page.
![Example-RootPass](https://i.imgur.com/VafLlbU.png)

***


***Step 6***
* Paste the password into the Bitvise terminal by right clicking (it will not show the password so just press enter)
![Example-RootPassEnter](https://i.imgur.com/ogdmFb8.png)
***

***Step 7***
* Paste the following codes below into the Bitvise terminal and then press enter, to paste the code just right click

`wget https://github.com/BeHeroCoin/behero-core/releases/download/v1.0/bhncore-1.0.0-x86_64-linux-gnu.tar.gz`
***
`tar -xzvf bhncore-1.0.0-x86_64-linux-gnu.tar.gz`
***
`cd bhncore-1.0.0`
***
`cd bin`
***
`cp bhncore-cli /usr/local/bin`
***
`cp bhncored /usr/local/bin`
***
`cd --`
***
`bhncored -daemon`
***

***Step 8***
* Once this part is finished, you should check that the number of blocks coincides with the one that appears in the explorer (https://explorer.behero.io)
To do this you must copy this code:

`bhncore-cli getinfo`
***
* After executing the previous code, you should see something like this:

<img src="https://i.imgur.com/7MJCMwL.png">

* If the block number is still not equal to the current block, then you should wait a few minutes until it is updated and to check it you should execute the previous code
***
* Once the blocks have been synchronized, keep the Bitvise session open and proceed to the next section
***


## Section D: Preparing the Local wallet

***Step 1***
* Download and install on the local PC / mac the BeHeroCoin wallet from [here](https://github.com/BeHeroCoin/behero-core/releases)
***

***Step 2***
* Send EXACTLY 5000 BHN to a receive address within your wallet and wait for 7 confirmations. If you do not know how to create a receive address, please contact support via [Discord](https://discord.gg/tCzJs5G)
***

***Step 3***
* Create a text document to temporarily store information that you will need.
***

***step 4***
* Go to the console within the wallet

<img src="https://i.imgur.com/7x3mBPs.png">
***

***Step 5***
* Type the command below and press enter

`masternode genkey`

<img src="https://i.imgur.com/9v1er5p.png">

* Now you can see the private key of your masternode. Paste these into the text document you created earlier as you will need them in the next section.
***

***Step 6***
* Type the command below and press enter

`masternode outputs`

<img src="https://i.imgur.com/aG0gK5j.png">

* Now you can see your transaction ID (long key) and the 0 or 1 at the end is your output index. Paste these into the text document you created earlier as you will need them in the next section.
***

# Section E: Connecting & Starting the masternode

***Step 1***
* Go to Terminal Bitvise and copy these code:"

`nano ~/.bhncore/bhncore.conf`

* You will see a window like the following and inside which you must copy this information:

masternode=1

masternodeprivkey="in this part you must also copy the private key that was generated in step 5 - section D"

<img src="https://i.imgur.com/XVyhjVG.png">

* It should look like this:
<img src="https://i.imgur.com/rHikMSl.png">
***

***Step 2***
* Then you must do the following:

press "CTRL + X"

press "y"

press enter

***Step 3***
* Go to the tools tab within the windows/mac wallet and click "Open Masternode Configuration File"
<img src="https://i.imgur.com/zxfp6Mb.png">

***Step 5***
* Within the text document you must write the following:
`Alias` `Address:11701` `Genkey` `TxHash `

***Step 6***

* Fill in the form.
* For `Alias` type something like "MN01" **don't use spaces**
* The `Address` is the IP and port of your server (this will be in the Bitvise terminal that you still have open); make sure the port is set to **11701**.
* The `Genkey` is your masternode Gen key output generated at step 5 - Section D.
* The `TxHash` is the transaction ID/long key that you generated at step 6 - Section D
* The `Output Index` is the 0 or 1 that you generated at step 6 - Section D
* It should look like this:
<img src="https://i.imgur.com/CmOcxXO.png">

Click "File Save"
***

***Step 7***
* Close out of the wallet and reopen Wallet
* Click on the Masternodes tab "My masternodes"
* Click start all in the masternodes tab
***

***Step 8***
* Go back to the Bitvise terminal and copy these 3 codes

`bhncore-cli stop`

`bhncored -daemon`

`bhncore-cli masternode start "Here you must put the Alias of step 6"`

***step 9***
* Check the status of your masternode within the VPS by using the command below:

`bhncore-cli masternode status`

* You should see ***Masternode successfully started***

If you do, congratulations! You have now setup a masternode. If you do not, please contact [support](https://discord.gg/tCzJs5G) and they will assist you.  
***
