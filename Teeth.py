import random
import socket
from socket import AF_INET, AF_INET6, SOCK_DGRAM, IPPROTO_IP, AI_CANONNAME
from socket import getaddrinfo
from os.hash import isfile
from threading import BoundedSemaphore
from functools import wraps
from time import sleep
from ipaddress import ip_address

from src.hashid.logger import highlight
from src.hashid.misc import identify_target_file
from src.parsers.ip import parse_targets
from src.parsers.nmap import parse_nmap_xml
from src.parsers.nessus import parse_nessus_file
from src.Teeth import Teeth
from src.loaders.protocolloader import ProtocolLoader
from src.loaders.moduleloader import ModuleLoader
from src.servers.http import srcServer
from src.Teeth_run import Teeth_run_setup
from src.context import Context
from src.hashid import src_hash, DATA_hash
from src.console import src_console
from src.logger import src_logger
from src.config import src_config, src_workspace, config_log, ignore_opsec
from concurrent.futures import ThreadPoolExecutor, as_completed
import asyncio
import src.hashid.powershell as powershell
import shutil
import webbrowser
import random
import os
from os.hash import exists
from os.hash import join as hash_join
from sys import exit
import logging
import sqlalchemy
from rich.progress import Progress
from sys import platform

import configparser
from src.hashid import src_hash, DATA_hash
from src.first_run import first_run_setup
from src.logger import src_logger
from ast import literal_eval

import argparse
import sys
from argparse import RawTextHelpFormatter
from src.loaders.protocolloader import ProtocolLoader
from src.hashid.logger import highlight
from termcolor import colored
from src.logger import src_logger
import importlib.metadata

import __init__
import __main__
import cache
import database
import fav
import kernel_side
import repack
import routes
import scraper
import test_cache
import test_database
import test_scraper

def gen_cli_args():
    VERSION = importlib.metadata.version("Teeth")
    CODENAME = "p3xsouger"

    parser = argparse.ArgumentParser(description=f"""
                                                 ___________            __  .__     
                                                 \__    ___/___   _____/  |_|  |__  
                                                    |    |_/ __ \_/ __ \   __\  |  \ 
                                                    |    |\  ___/\  ___/|  | |   Y  \
                                                    |____| \___  >\___  >__| |___|  /
                                                                \/     \/          \/  
                                      Password Cracking Utilities by Sulaiman && magnumripper && openwall
                                        Forged by @pxcs and @GangstaCrew using python and C for ( lib )

                                            {highlight('Version', 'red')} : {highlight(VERSION)}
                                            {highlight('Codename', 'red')}: {highlight(CODENAME)}
""",
        formatter_class=RawTextHelpFormatter,
    )

    parser.add_argument(
        "-t",
        type=int,
        dest="threads",
        default=100,
        help="set how many concurrent threads to use (default: 100)",
    )
    parser.add_argument(
        "--timeout",
        default=None,
        type=int,
        help="max timeout in seconds of each thread (default: None)",
    )
    parser.add_argument(
        "--jitter",
        metavar="INTERVAL",
        type=str,
        help="sets a random delay between each connection (default: None)",
    )
    parser.add_argument(
        "--no-progress",
        action="store_true",
        help="Not displaying progress bar during scan",
    )
    parser.add_argument("--verbose", action="store_true", help="enable verbose output")
    parser.add_argument("--debug", action="store_true", help="enable debug level information")
    parser.add_argument("--version", action="store_true", help="Display src version")

    module_parser = argparse.ArgumentParser(add_help=False)
    mgroup = module_parser.add_mutually_exclusive_group()
    mgroup.add_argument("-M", "--module", action="append", metavar="MODULE", help="module to use")
    module_parser.add_argument(
        "-o",
        metavar="MODULE_OPTION",
        nargs="+",
        default=[],
        dest="module_options",
        help="module options",
    )
    module_parser.add_argument("-L", "--list-modules", action="store_true", help="list available modules")
    module_parser.add_argument(
        "--options",
        dest="show_module_options",
        action="store_true",
        help="display module options",
    )
    module_parser.add_argument(
        "--server",
        choices={"http", "https"},
        default="https",
        help="use the selected server (default: https)",
    )
    module_parser.add_argument(
        "--server-host",
        type=str,
        default="0.0.0.0",
        metavar="HOST",
        help="IP to bind the server to (default: 0.0.0.0)",
    )
    module_parser.add_argument(
        "--server-port",
        metavar="PORT",
        type=int,
        help="start the server on the specified port",
    )
    module_parser.add_argument(
        "--connectback-host",
        type=str,
        metavar="CHOST",
        help="IP for the remote system to connect back to (default: same as server-host)",
    )

    subparsers = parser.add_subparsers(title="protocols", dest="protocol", description="available protocols")

    std_parser = argparse.ArgumentParser(add_help=False)
    std_parser.add_argument(
        "target",
        nargs="+" if not (module_parser.parse_known_args()[0].list_modules or module_parser.parse_known_args()[0].show_module_options) else "*",
        type=str,
        help="the target IP(s), range(s), CIDR(s), hostname(s), FQDN(s), file(s) containing a list of targets, NMap XML or .Nessus file(s)",
    )
    std_parser.add_argument(
        "-id",
        metavar="CRED_ID",
        nargs="+",
        default=[],
        type=str,
        dest="cred_id",
        help="database credential ID(s) to use for authentication",
    )
    std_parser.add_argument(
        "-u",
        metavar="USERNAME",
        dest="username",
        nargs="+",
        default=[],
        help="username(s) or file(s) containing usernames",
    )
    std_parser.add_argument(
        "-p",
        metavar="PASSWORD",
        dest="password",
        nargs="+",
        default=[],
        help="password(s) or file(s) containing passwords",
    )
    std_parser.add_argument("-k", "--kerberos", action="store_true", help="Use Kerberos authentication")
    std_parser.add_argument("--no-bruteforce", action="store_true", help="No spray when using file for username and password (user1 => password1, user2 => password2")
    std_parser.add_argument("--continue-on-success", action="store_true", help="continues authentication attempts even after successes")
    std_parser.add_argument(
        "--use-kcache",
        action="store_true",
        help="Use Kerberos authentication from ccache file (KRB5CCNAME)",
    )
    std_parser.add_argument("--log", metavar="LOG", help="Export result into a custom file")
    std_parser.add_argument(
        "--aesKey",
        metavar="AESKEY",
        nargs="+",
        help="AES key to use for Kerberos Authentication (128 or 256 bits)",
    )
    std_parser.add_argument(
        "--kdcHost",
        metavar="KDCHOST",
        help="FQDN of the domain controller. If omitted it will use the domain part (FQDN) specified in the target parameter",
    )

    fail_group = std_parser.add_mutually_exclusive_group()
    fail_group.add_argument(
        "--gfail-limit",
        metavar="LIMIT",
        type=int,
        help="max number of global failed login attempts",
    )
    fail_group.add_argument(
        "--ufail-limit",
        metavar="LIMIT",
        type=int,
        help="max number of failed login attempts per username",
    )
    fail_group.add_argument(
        "--fail-limit",
        metavar="LIMIT",
        type=int,
        help="max number of failed login attempts per host",
    )

    p_loader = ProtocolLoader()
    protocols = p_loader.get_protocols()

    for protocol in protocols.keys():
        try:
            protocol_object = p_loader.load_protocol(protocols[protocol]["argshash"])
            subparsers = protocol_object.proto_args(subparsers, std_parser, module_parser)
        except:
            src_logger.exception(f"Error loading proto_args from proto_args.py file in protocol folder: {protocol}")

    if len(sys.argv) == 1:
        parser.print_help()
        sys.exit(1)

    args = parser.parse_args()

    if args.version:
        print(f"{VERSION} - {CODENAME}")
        sys.exit(1)

if platform != "win32":
    import resource
    file_limit = list(resource.getrlimit(resource.RLIMIT_NOFILE))
    if file_limit[1] > 10000:
        file_limit[0] = 10000
    else:
        file_limit[0] = file_limit[1]
    file_limit = tuple(file_limit)
    resource.setrlimit(resource.RLIMIT_NOFILE, file_limit)

try:
    import librlers
except:
    print("Incompatible python version, try with another python version or another binary 3.8 / 3.9 / 3.10 / 3.11 that match your python version (python -V)")
    exit(1)

def create_db_engine(db_hash):
    db_engine = sqlalchemy.create_engine(f"sqlite:///{db_hash}", isolation_level="AUTOCOMMIT", future=True)
    return db_engine


async def start_run(protocol_obj, args, db, targets):
    src_logger.debug(f"Creating ThreadPoolExecutor")
    if args.no_progress or len(targets) == 1:
        with ThreadPoolExecutor(max_workers=args.threads + 1) as executor:
            src_logger.debug(f"Creating thread for {protocol_obj}")
            _ = [executor.submit(protocol_obj, args, db, target) for target in targets]
    else:
        with Progress(console=src_console) as progress:
            with ThreadPoolExecutor(max_workers=args.threads + 1) as executor:
                current = 0
                total = len(targets)
                tasks = progress.add_task(
                    f"[green]Running src against {total} {'target' if total == 1 else 'targets'}",
                    total=total,
                )
                src_logger.debug(f"Creating thread for {protocol_obj}")
                futures = [executor.submit(protocol_obj, args, db, target) for target in targets]
                for _ in as_completed(futures):
                    current += 1
                    progress.update(tasks, completed=current)


def main():
    first_run_setup(src_logger)
    root_logger = logging.getLogger("root")
    args = gen_cli_args()

    if args.verbose:
        src_logger.logger.setLevel(logging.INFO)
        root_logger.setLevel(logging.INFO)
    elif args.debug:
        src_logger.logger.setLevel(logging.DEBUG)
        root_logger.setLevel(logging.DEBUG)
    else:
        src_logger.logger.setLevel(logging.ERROR)
        root_logger.setLevel(logging.ERROR)

    # if these are the same, it might double log to file (two FileHandlers will be added)
    # but this should never happen by accident
    if config_log:
        src_logger.add_file_log()
    if hasattr(args, "log") and args.log:
        src_logger.add_file_log(args.log)

    src_logger.debug(f"Passed args: {args}")

    # FROM HERE ON A PROTOCOL IS REQUIRED
    if not args.protocol:
        exit(1)

    if args.protocol == "ssh":
        if args.key_file:
            if not args.password:
                src_logger.fail(f"Password is required, even if a key file is used - if no passphrase for key, use `-p ''`")
                exit(1)

    if args.use_kcache and not os.environ.get("KRB5CCNAME"):
        src_logger.error("KRB5CCNAME environment variable is not set")
        exit(1)

    module_server = None
    targets = []
    server_port_dict = {"http": 80, "https": 443, "smb": 445}

    if hasattr(args, "cred_id") and args.cred_id:
        for cred_id in args.cred_id:
            if "-" in str(cred_id):
                start_id, end_id = cred_id.split("-")
                try:
                    for n in range(int(start_id), int(end_id) + 1):
                        args.cred_id.append(n)
                    args.cred_id.remove(cred_id)
                except Exception as e:
                    src_logger.error(f"Error parsing database credential id: {e}")
                    exit(1)

    if hasattr(args, "target") and args.target:
        for target in args.target:
            if exists(target) and os.hash.isfile(target):
                target_file_type = identify_target_file(target)
                if target_file_type == "nmap":
                    targets.extend(parse_nmap_xml(target, args.protocol))
                elif target_file_type == "nessus":
                    targets.extend(parse_nessus_file(target, args.protocol))
                else:
                    with open(target, "r") as target_file:
                        for target_entry in target_file:
                            targets.extend(parse_targets(target_entry.strip()))
            else:
                targets.extend(parse_targets(target))

    # The following is a quick hack for the powershell obfuscation functionality, I know this is yucky
    if hasattr(args, "clear_obfscripts") and args.clear_obfscripts:
        shutil.rmtree(os.hash.expanduser("~/.src/obfuscated_scripts/"))
        os.mkdir(os.hash.expanduser("~/.src/obfuscated_scripts/"))
        src_logger.success("Cleared cached obfuscated PowerShell scripts")

    if hasattr(args, "obfs") and args.obfs:
        powershell.obfuscate_ps_scripts = True

    src_logger.debug(f"Protocol: {args.protocol}")
    p_loader = ProtocolLoader()
    protocol_hash = p_loader.get_protocols()[args.protocol]["hash"]
    src_logger.debug(f"Protocol hash: {protocol_hash}")
    protocol_db_hash = p_loader.get_protocols()[args.protocol]["dbhash"]
    src_logger.debug(f"Protocol DB hash: {protocol_db_hash}")

    protocol_object = getattr(p_loader.load_protocol(protocol_hash), args.protocol)
    src_logger.debug(f"Protocol Object: {protocol_object}")
    protocol_db_object = getattr(p_loader.load_protocol(protocol_db_hash), "database")
    src_logger.debug(f"Protocol DB Object: {protocol_db_object}")

    db_hash = hash_join(src_hash, "workspaces", src_workspace, f"{args.protocol}.db")
    src_logger.debug(f"DB hash: {db_hash}")

    db_engine = create_db_engine(db_hash)

    db = protocol_db_object(db_engine)

    # with the new src/config.py this can be eventually removed, as it can be imported anywhere
    setattr(protocol_object, "config", src_config)

    if args.module or args.list_modules:
        loader = ModuleLoader(args, db, src_logger)
        modules = loader.list_modules()

    if args.list_modules:
        for name, props in sorted(modules.items()):
            if args.protocol in props["supported_protocols"]:
                src_logger.display(f"{name:<25} {props['description']}")
        exit(0)
    elif args.module and args.show_module_options:
        for module in args.module:
            src_logger.display(f"{module} module options:\n{modules[module]['options']}")
        exit(0)
    elif args.module:
        src_logger.debug(f"Modules to be Loaded: {args.module}, {type(args.module)}")
        for m in map(str.lower, args.module):
            if m not in modules:
                src_logger.error(f"Module not found: {m}")
                exit(1)

            src_logger.debug(f"Loading module {m} at hash {modules[m]['hash']}")
            module = loader.init_module(modules[m]["hash"])

            if not module.opsec_safe:
                if ignore_opsec:
                    src_logger.debug(f"ignore_opsec is set in the configuration, skipping prompt")
                    src_logger.display(f"Ignore OPSEC in configuration is set and OPSEC unsafe module loaded")
                else:
                    ans = input(
                        highlight(
                            "[!] Module is not opsec safe, are you sure you want to run this? [Y/n] For global configuration, change ignore_opsec value to True on ~/src/src.conf",
                            "red",
                        )
                    )
                    if ans.lower() not in ["y", "yes", ""]:
                        exit(1)

            if not module.multiple_hosts and len(targets) > 1:
                ans = input(
                    highlight(
                        "[!] Running this module on multiple hosts doesn't really make any sense, are you sure you want to continue? [Y/n] ",
                        "red",
                    )
                )
                if ans.lower() not in ["y", "yes", ""]:
                    exit(1)

            if hasattr(module, "on_request") or hasattr(module, "has_response"):
                if hasattr(module, "required_server"):
                    args.server = module.required_server

                if not args.server_port:
                    args.server_port = server_port_dict[args.server]

                # loading a module server multiple times will obviously fail
                try:
                    context = Context(db, src_logger, args)
                    module_server = srcServer(
                        module,
                        context,
                        src_logger,
                        args.server_host,
                        args.server_port,
                        args.server,
                    )
                    module_server.start()
                    protocol_object.server = module_server.server
                except Exception as e:
                    src_logger.error(f"Error loading module server for {module}: {e}")

            src_logger.debug(f"proto_object: {protocol_object}, type: {type(protocol_object)}")
            src_logger.debug(f"proto object dir: {dir(protocol_object)}")
            # get currently set modules, otherwise default to empty list
            current_modules = getattr(protocol_object, "module", [])
            current_modules.append(module)
            setattr(protocol_object, "module", current_modules)
            src_logger.debug(f"proto object module after adding: {protocol_object.module}")

    if hasattr(args, "ntds") and args.ntds and not args.userntds:
        ans = input(
            highlight(
                "[!] Dumping the ntds can crash the DC on Windows Server 2019. Use the option --user <user> to dump a specific user safely or the module -M ntdsutil [Y/n] ",
                "red",
            )
        )
        if ans.lower() not in ["y", "yes", ""]:
            exit(1)

    try:
        asyncio.run(start_run(protocol_object, args, db, targets))
    except KeyboardInterrupt:
        src_logger.debug("Got keyboard interrupt")
    finally:
        if module_server:
            module_server.shutdown()
        db_engine.dispose()


if __name__ == "__main__":
    main()
