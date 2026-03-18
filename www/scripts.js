document.addEventListener("DOMContentLoaded", function() {
    // Havai fişek efekti
    const createFirework = () => {
        const firework = document.createElement("div");
        firework.className = "firework";
        document.body.appendChild(firework);

        firework.style.left = `${Math.random() * 100}%`;
        firework.style.animationDuration = `${Math.random() * 2 + 1}s`;

        setTimeout(() => {
            firework.remove();
        }, 3000);
    };

    for (let i = 0; i < 10; i++) {
        setTimeout(createFirework, i * 300);
    }

    // Mouse hareketi efekti
    document.addEventListener("mousemove", function(e) {
        const spark = document.createElement("div");
        spark.className = "spark";
        spark.style.left = `${e.clientX}px`;
        spark.style.top = `${e.clientY}px`;
        document.body.appendChild(spark);

        setTimeout(() => {
            spark.remove();
        }, 1000);
    });
});