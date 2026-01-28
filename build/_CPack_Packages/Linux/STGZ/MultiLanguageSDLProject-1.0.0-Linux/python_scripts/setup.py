from setuptools import setup, find_packages

setup(
    name="multilanguage-sdl-python",
    version="1.0.0",
    description="Python component of Multi-Language SDL Project",
    author="Developer",
    author_email="developer@example.com",
    packages=find_packages(),
    install_requires=[
        "pygame>=2.0.0"
    ],
    entry_points={
        'console_scripts': [
            'python_sdl_app=python.sdl_app:main',
        ],
    },
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.6',
)