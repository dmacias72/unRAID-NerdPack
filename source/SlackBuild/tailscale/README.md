# Tailscale

> "Private WireGuard® networks made easy"
> <br/> https://github.com/tailscale/tailscale

### Using

See https://www.tailscale.com to sign up and https://tailscale.com/kb/ for general usage information.

Manual package installation and usage for Unraid:

> :bulb: *Each step is performed **one-time** as initial setup, whereafter Tailscale will be logged in and running automatically on boot.*

1. Create persisted directory
    ```console
    root@unraid:~# mkdir /boot/config/tailscale
    ```
    
2. Download `tailscale_XXX.txz` and move to `/boot/config/tailscale`
    ```console
    root@unraid:~# cd /boot/config/tailscale
    root@unraid:/boot/config/tailscale# wget <url-of-tailscale-XXX.txz>
    ```
3. Create empty `tailscaled.state` file
    ```console
    root@unraid:~# touch /boot/config/tailscale/tailscaled.state
    ```
    
4. Append the following to `/boot/config/go`
    ```bash
    installpkg /boot/config/tailscale/tailscale-XXX.txz
    ln -s /boot/config/tailscale/tailscaled.state /var/lib/tailscale/tailscaled.state
    /usr/sbin/tailscaled &
    ```
    
5. Stop file

  * a) If `/boot/config/stop` does not exist create it
      ```console
      root@unraid:~# echo -e '#!/bin/bash\n' > /boot/config/stop
      root@unraid:~# chmod +x /boot/config/stop
      ```
    
  * b) Append the following to `/boot/config/stop`
      ```bash
      killall tailscaled
      /usr/sbin/tailscaled --cleanup
      ```
      
6. Reboot Unraid

7. Authenticate by URL
    ```console
    root@unraid:~# tailscale up
  
    To authenticate, visit:

        https://login.tailscale.com/a/abc123abc123
    ```
    
 8. Check Tailscale IP and ping test server
    ```console
    root@unraid:~# ip -4 addr show tailscale0
    21: tailscale0: <POINTOPOINT,MULTICAST,NOARP,UP,LOWER_UP> mtu 1280 qdisc fq state UNKNOWN group default qlen 500
    inet 100.XXX.XXX.XXX/32 scope global tailscale0
       valid_lft forever preferred_lft forever
    
    root@unraid:~# ping -c 1 100.101.102.103
    PING 100.101.102.103 (100.101.102.103) 56(84) bytes of data.
    64 bytes from 100.101.102.103: icmp_seq=1 ttl=64 time=90.5 ms
    
    ---100.101.102.103 ping statistics ---
    1 packets transmitted, 1 received, 0% packet loss, time 0ms
    rtt min/avg/max/mdev = 90.476/90.476/90.476/0.000 ms
    ```
    
From here you're all set. Unraid is connected to Tailscale. You should be able to install and setup Tailscale on a
personal device and access your Unraid server from anywhere over your Tailscale VPN connection. No port-forwarding required.
